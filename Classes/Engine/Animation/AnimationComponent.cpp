//
//  AnimationComponent.cpp
//  BouncyHouse
//
//  Created by Derek Peterson on 12/2/15.
//
//

#include "AnimationComponent.h"
#include "AnimationSystem.h"
#include "../Entity/EntitySystem.h"
#include "../Event/EventManager.h"
#include "../Physics/PhysicsComponent.h"
#include "../Render/RenderComponent.h"

std::string AnimationComponent::s_componentType = "AnimationComponent";

void AnimationComponent::DNADataInit( EntityHandle i_entityHandle, const rapidjson::Value& i_dnaObject )
{
    m_entityHandle = i_entityHandle;
    AnimationSystem::GetInstance()->RegisterComponent( this );
    
    ASSERTS( i_dnaObject.HasMember( "AnimTree" ), "AnimationComponent not configured with AnimTree!" );
    if ( i_dnaObject.HasMember( "AnimTree" ) )
    {
        m_animTree = AnimTree::CreateWithDNA( m_entityHandle, i_dnaObject["AnimTree"].GetString() );
    }
    
    if ( i_dnaObject.HasMember( "Motions" ) )
    {
        for ( unsigned int i = 0; i < i_dnaObject["Motions"].Capacity(); i++ )
        {
            std::string pMotionName = i_dnaObject["Motions"][i]["Motion"].GetString();
            std::string pSpriteName = i_dnaObject["Motions"][i]["Name"].GetString();
            int pStartFrame = i_dnaObject["Motions"][i]["StartFrame"].GetInt();
            int pEndFrame = i_dnaObject["Motions"][i]["EndFrame"].GetInt();
            float pMotionRate = -1.0f;
            if ( i_dnaObject["Motions"][i].HasMember("MotionRate") )
            {
                pMotionRate = i_dnaObject["Motions"][i]["MotionRate"].GetDouble();
            }
            
            char pChar[200];
            sprintf( pChar, "%s_%s", pMotionName.c_str(), pSpriteName.c_str() );
            std::string pAnimationName = std::string( pChar );
        
            MotionInfo pMotionInfo = MotionInfo( pAnimationName, pSpriteName, pMotionRate, pStartFrame, pEndFrame );
            m_motions.insert( std::make_pair( pMotionName, pMotionInfo ) );
        }
    }
}

AnimationComponent::~AnimationComponent()
{
    AnimationSystem::GetInstance()->UnregisterComponent( this );
    delete m_animTree;
}

void AnimationComponent::OnActivate()
{
    for ( std::map<std::string, MotionInfo>::iterator it = m_motions.begin(); it != m_motions.end(); it++ )
    {
        MotionInfo pMotionInfo = it->second;
        
        int pFrameCount = pMotionInfo.m_endFrame - pMotionInfo.m_startFrame + 1;
        
        cocos2d::Vector<cocos2d::SpriteFrame*> pFrames( pFrameCount );
        for ( int i = pMotionInfo.m_startFrame; i <= pMotionInfo.m_endFrame; i++ )
        {
            char pFrameName[100] = {0};
            sprintf( pFrameName, "%s_%02d.png", pMotionInfo.m_spriteName.c_str(), i );
            pFrames.pushBack( cocos2d::SpriteFrameCache::getInstance()->getSpriteFrameByName( pFrameName ) );
        }
        
        cocos2d::Animation* pAnimation = cocos2d::Animation::createWithSpriteFrames( pFrames, 1.0f / 30.0f );
        cocos2d::AnimationCache::getInstance()->addAnimation( pAnimation, pMotionInfo.m_animationName );
    }

    if ( m_animTree )
    {
        m_animTree->Start();
    }
}

void AnimationComponent::OnDeactivate()
{
    if ( m_animTree )
    {
        m_animTree->Stop();
    }
}

void AnimationComponent::StartMotion( std::string i_motionName, int i_loops )
{
    ASSERTS( m_motions.find( i_motionName ) != m_motions.end(), "Starting missing motion" );
    MotionInfo pMotionInfo = m_motions.at( i_motionName );
    cocos2d::Animation* pAnimation = cocos2d::AnimationCache::getInstance()->getAnimation( pMotionInfo.m_animationName );
    if ( pAnimation )
    {
        pAnimation->setLoops( i_loops );
        cocos2d::Action* pAction = cocos2d::Animate::create( pAnimation );
        
        auto pCallback = cocos2d::CallFunc::create( CC_CALLBACK_0( AnimationComponent::OnMotionEnd, this ) );
        pAction = cocos2d::Sequence::create( (cocos2d::FiniteTimeAction*) pAction, pCallback, NULL);
        
        if ( pMotionInfo.m_motionRate > 0.0f )
        {
            pAction = cocos2d::Speed::create( (cocos2d::ActionInterval*) pAction, 1.0f );
        }
        
        pAction->setTag( ActionTag::AnimationAction );
        
        RenderComponent* pRenderComponent = EntitySystem::GetInstance()->GetComponent<RenderComponent>( m_entityHandle );
        if ( pRenderComponent )
        {
            pRenderComponent->m_sprite->runAction( pAction );
        }
        m_currentMotionName = i_motionName;

    }
    m_motionInterrupted = false;
}

void AnimationComponent::StopMotion()
{
    RenderComponent* pRenderComponent = EntitySystem::GetInstance()->GetComponent<RenderComponent>( m_entityHandle );
    if ( pRenderComponent )
    {
        cocos2d::Action* pCurrentAnimation = pRenderComponent->m_sprite->getActionByTag( ActionTag::AnimationAction );
        if ( pCurrentAnimation )
        {
            pRenderComponent->m_sprite->stopAction( pCurrentAnimation );
            m_motionInterrupted = true;
        }
    }
}

void AnimationComponent::SyncMotionRate()
{
    RenderComponent* pRenderComponent = EntitySystem::GetInstance()->GetComponent<RenderComponent>( m_entityHandle );
    if ( pRenderComponent )
    {
        cocos2d::Action* pCurrentAnimation = pRenderComponent->m_sprite->getActionByTag( ActionTag::AnimationAction );
        cocos2d::Speed* pSpeedAction = dynamic_cast<cocos2d::Speed*>( pCurrentAnimation );
        if ( pCurrentAnimation && pSpeedAction )
        {
            PhysicsComponent* pPhysicsComponent = EntitySystem::GetInstance()->GetComponent<PhysicsComponent>( m_entityHandle );
            if ( pPhysicsComponent )
            {
                float pMovementRate = fabs( pPhysicsComponent->GetVelocity().x );
                float pMotionRate = m_motions.at( m_currentMotionName ).m_motionRate;
                float pAdjustedRate = pMovementRate / pMotionRate;
                pSpeedAction->setSpeed( pAdjustedRate );
            }
        }
    }
}

void AnimationComponent::OnMotionEnd()
{
    EventManager::GetInstance()->SendEvent( "MotionEnd", &m_entityHandle );
    if ( !m_motionInterrupted && m_animTree )
    {
        m_animTree->ExitState();
    }
}


