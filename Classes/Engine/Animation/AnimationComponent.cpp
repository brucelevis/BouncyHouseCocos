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

using namespace cocos2d;

std::string AnimationComponent::s_componentType = "AnimationComponent";

void AnimationComponent::Init( EntityHandle i_entityHandle, const rapidjson::Value& i_dnaObject )
{
    m_entityHandle = i_entityHandle;
    AnimationSystem::RegisterComponent( this );
    
    if ( i_dnaObject.HasMember( "Motions" ) )
    {
        for ( int i = 0; i < i_dnaObject["Motions"].Capacity(); i++ )
        {
            std::string pMotionName = i_dnaObject["Motions"][i]["Motion"].GetString();
            std::string pSpriteName = i_dnaObject["Motions"][i]["Name"].GetString();
            float pFrameCount = i_dnaObject["Motions"][i]["Frames"].GetDouble();
            float pMotionRate = -1.0f;
            if ( i_dnaObject["Motions"][i].HasMember("MotionRate") )
            {
                pMotionRate = i_dnaObject["Motions"][i]["MotionRate"].GetDouble();
            }
            
            Vector<SpriteFrame*> pFrames( pFrameCount );
            for ( int i = 0; i < pFrameCount; i++ )
            {
                char pFrameName[100] = {0};
                sprintf( pFrameName, "%s_%02d.png", pSpriteName.c_str(), i );
                pFrames.pushBack( SpriteFrameCache::getInstance()->getSpriteFrameByName( pFrameName ) );
            }
            
            Animation* pAnimation = Animation::createWithSpriteFrames( pFrames, 1.0f / 30.0f );
            AnimationCache::getInstance()->addAnimation( pAnimation, pSpriteName );
            
            MotionInfo pMotionInfo = MotionInfo( pSpriteName, pMotionRate );
            
            m_motions.insert( std::make_pair( pMotionName, pMotionInfo ) );
        }
    }
}

void AnimationComponent::Activate()
{
    StartMotion( "Run", -1 );
}

AnimationComponent::~AnimationComponent() 
{
    AnimationSystem::UnregisterComponent( this );
}

void AnimationComponent::StartMotion( std::string i_motionName, float i_loops )
{
    MotionInfo pMotionInfo = m_motions.at( i_motionName );
    Animation* pAnimation = AnimationCache::getInstance()->getAnimation( pMotionInfo.m_animationName );
    if ( pAnimation )
    {
        pAnimation->setLoops( i_loops );
        Action* pAction;
        if ( pMotionInfo.m_motionRate > 0.0f )
        {
            Animate* pAnimate = Animate::create( pAnimation );
            pAction = Speed::create( pAnimate, 1.0f );
        }
        else
        {
            pAction = Animate::create( pAnimation );
        }
        pAction->setTag( ActionTag::AnimationAction );
        
        RenderComponent* pRenderComponent = EntitySystem::GetComponent<RenderComponent>( m_entityHandle );
        if ( pRenderComponent )
        {
            Action* pCurrentAnimation = pRenderComponent->m_sprite->getActionByTag( ActionTag::AnimationAction );
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
    RenderComponent* pRenderComponent = EntitySystem::GetComponent<RenderComponent>( m_entityHandle );
    if ( pRenderComponent )
    {
        Action* pCurrentAnimation = pRenderComponent->m_sprite->getActionByTag( ActionTag::AnimationAction );
        Speed* pSpeedAction = dynamic_cast<Speed*>( pCurrentAnimation );
        if ( pCurrentAnimation && pSpeedAction )
        {
            PhysicsComponent* pPhysicsComponent = EntitySystem::GetComponent<PhysicsComponent>( m_entityHandle );
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