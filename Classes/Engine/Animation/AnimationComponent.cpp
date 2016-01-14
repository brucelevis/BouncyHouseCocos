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
#include "../Physics/PhysicsComponent.h"
#include "../Render/RenderComponent.h"

std::string AnimationComponent::s_componentType = "AnimationComponent";

void AnimationComponent::DNADataInit( EntityHandle i_entityHandle, const rapidjson::Value& i_dnaObject )
{
    m_entityHandle = i_entityHandle;
    AnimationSystem::GetInstance()->RegisterComponent( this );
    
    if ( i_dnaObject.HasMember( "Motions" ) )
    {
        for ( unsigned int i = 0; i < i_dnaObject["Motions"].Capacity(); i++ )
        {
            std::string pMotionName = i_dnaObject["Motions"][i]["Motion"].GetString();
            std::string pSpriteName = i_dnaObject["Motions"][i]["Name"].GetString();
            int pStartFrame = i_dnaObject["Motions"][i]["StartFrame"].GetInt();
            int pEndFrame = i_dnaObject["Motions"][i]["EndFrame"].GetInt();
            int pFrameCount = pEndFrame - pStartFrame + 1;
            float pMotionRate = -1.0f;
            if ( i_dnaObject["Motions"][i].HasMember("MotionRate") )
            {
                pMotionRate = i_dnaObject["Motions"][i]["MotionRate"].GetDouble();
            }
            
            cocos2d::Vector<cocos2d::SpriteFrame*> pFrames( pFrameCount );
            for ( int i = pStartFrame; i <= pEndFrame; i++ )
            {
                char pFrameName[100] = {0};
                sprintf( pFrameName, "%s_%02d.png", pSpriteName.c_str(), i );
                pFrames.pushBack( cocos2d::SpriteFrameCache::getInstance()->getSpriteFrameByName( pFrameName ) );
            }
            
            char pChar[200];
            sprintf( pChar, "%s_%s", pMotionName.c_str(), pSpriteName.c_str() );
            std::string pAnimationName = std::string( pChar );
            cocos2d::Animation* pAnimation = cocos2d::Animation::createWithSpriteFrames( pFrames, 1.0f / 30.0f );
            cocos2d::AnimationCache::getInstance()->addAnimation( pAnimation, pAnimationName );
            
            MotionInfo pMotionInfo = MotionInfo( pAnimationName, pMotionRate );
            
            m_motions.insert( std::make_pair( pMotionName, pMotionInfo ) );
        }
    }
}

AnimationComponent::~AnimationComponent()
{
    AnimationSystem::GetInstance()->UnregisterComponent( this );
}

void AnimationComponent::OnActivate()
{
    StartMotion( "Run", 999999 );
}

void AnimationComponent::StartMotion( std::string i_motionName, float i_loops, cocos2d::Action* i_nextAction )
{
    MotionInfo pMotionInfo = m_motions.at( i_motionName );
    cocos2d::Animation* pAnimation = cocos2d::AnimationCache::getInstance()->getAnimation( pMotionInfo.m_animationName );
    if ( pAnimation )
    {
        pAnimation->setLoops( i_loops );
        cocos2d::Action* pAction;
        if ( pMotionInfo.m_motionRate > 0.0f )
        {
            cocos2d::Animate* pAnimate = cocos2d::Animate::create( pAnimation );
            pAction = cocos2d::Speed::create( pAnimate, 1.0f );
        }
        else
        {
            pAction = cocos2d::Animate::create( pAnimation );
        }
        pAction->setTag( ActionTag::AnimationAction );
        
        if ( i_nextAction )
        {
            pAction = cocos2d::Sequence::create( (cocos2d::FiniteTimeAction*) pAction, i_nextAction, NULL);
        }
        
        RenderComponent* pRenderComponent = EntitySystem::GetInstance()->GetComponent<RenderComponent>( m_entityHandle );
        if ( pRenderComponent )
        {
            cocos2d::Action* pCurrentAnimation = pRenderComponent->m_sprite->getActionByTag( ActionTag::AnimationAction );
            if ( strcmp( i_motionName.c_str(), m_currentMotionName.c_str() ) != 0 || !pCurrentAnimation || pCurrentAnimation->isDone() )
            {
                if ( pCurrentAnimation && !pCurrentAnimation->isDone() )
                {
                    pRenderComponent->m_sprite->stopAction( pCurrentAnimation );
                }
                pRenderComponent->m_sprite->runAction( pAction );
                m_currentMotionName = i_motionName;
            }
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
