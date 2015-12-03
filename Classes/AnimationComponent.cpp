//
//  AnimationComponent.cpp
//  BouncyHouse
//
//  Created by Derek Peterson on 12/2/15.
//
//

#include "AnimationComponent.h"
#include "AnimationSystem.h"
#include "EntitySystem.h"
#include "RenderComponent.h"

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
            
            Vector<SpriteFrame*> pFrames( pFrameCount );
            for ( int i = 0; i < pFrameCount; i++ )
            {
                char pFrameName[100] = {0};
                sprintf( pFrameName, "%s_%02d.png", pSpriteName.c_str(), i );
                pFrames.pushBack( SpriteFrameCache::getInstance()->getSpriteFrameByName( pFrameName ) );
            }
            
            Animation* pAnimation = Animation::createWithSpriteFrames( pFrames, 1.0f / 30.0f );
            AnimationCache::getInstance()->addAnimation( pAnimation, pSpriteName );
            
            m_animationNames.insert( std::make_pair( pMotionName, pSpriteName ) );
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
    std::string pAnimationName = m_animationNames.at( i_motionName );
    Animation* pAnimation = AnimationCache::getInstance()->getAnimation( pAnimationName );
    if ( pAnimation )
    {
        pAnimation->setLoops( i_loops );
        Animate* pAnimate = Animate::create( pAnimation );
        pAnimate->setTag( ActionTag::AnimationAction );
        
        RenderComponent* pRenderComponent = EntitySystem::GetComponent<RenderComponent>( m_entityHandle );
        if ( pRenderComponent )
        {
            Action* pCurrentAnimation = pRenderComponent->m_sprite->getActionByTag( ActionTag::AnimationAction );
            if ( strcmp( i_motionName.c_str(), m_currentMotion.c_str() ) != 0 || !pCurrentAnimation || pCurrentAnimation->isDone() )
            {
                if ( pCurrentAnimation && !pCurrentAnimation->isDone() )
                {
                    pRenderComponent->m_sprite->stopAction( pCurrentAnimation );
                }
                pRenderComponent->m_sprite->runAction( pAnimate );
                m_currentMotion = i_motionName;
            }
        }
    }
}