//
//  AnimationSystem.cpp
//  BouncyHouse
//
//  Created by Derek Peterson on 12/2/15.
//
//

#include "AnimationComponent.h"
#include "AnimationSystem.h"
#include "EntitySystem.h"
#include "PhysicsComponent.h"
#include "RenderComponent.h"
#include "RenderSystem.h"

std::map<EntityHandle, Component*> AnimationSystem::m_components;
bool AnimationSystem::m_debug;

void AnimationSystem::RegisterComponent( Component* i_component )
{
    m_components.insert( std::make_pair( i_component->m_entityHandle, i_component ) );
}

void AnimationSystem::UnregisterComponent( Component* i_component )
{
    m_components.erase( i_component->m_entityHandle );
}
void AnimationSystem::Update( float i_dt )
{
    int i = 0;
    for ( std::map<EntityHandle, Component*>::iterator it = m_components.begin(); it != m_components.end(); it++ )
    {
        AnimationComponent* pComponent = (AnimationComponent*) it->second;
        if ( pComponent )
        {
            pComponent->SyncMotionRate();

#ifdef DEBUG
            if ( m_debug )
            {
                cocos2d::Vec2 pPosition;
                std::string pMotionName = pComponent->GetCurrentMotionName();
                std::string pAnimationName;
                int pFrameIndex = -1;
                int pFrameCount = -1;
                float pAnimRate = 1.0f;
                RenderComponent* pRenderComponent = EntitySystem::GetComponent<RenderComponent>( pComponent->m_entityHandle );
                if ( pRenderComponent )
                {
                    cocos2d::Action* pAction = pRenderComponent->m_sprite->getActionByTag( ActionTag::AnimationAction );
                    if ( pAction && !pAction->isDone() )
                    {
                        cocos2d::Animate* pAnimate = dynamic_cast<cocos2d::Animate*>( pAction );
                        if ( !pAnimate )
                        {
                            cocos2d::Speed* pSpeed = dynamic_cast<cocos2d::Speed*>( pAction );
                            if ( pSpeed )
                            {
                                pAnimRate = pSpeed->getSpeed();
                                pAnimate = dynamic_cast<cocos2d::Animate*>( pSpeed->getInnerAction() );
                            }
                        }
                        if ( pAnimate )
                        {
                            pFrameIndex = pAnimate->getCurrentFrameIndex();
                        }
                    }
                    
                    
                    MotionInfo pMotionInfo = pComponent->GetCurrentMotion();
                    pAnimationName = pMotionInfo.m_animationName;
                    cocos2d::Animation* pAnimation = cocos2d::AnimationCache::getInstance()->getAnimation( pMotionInfo.m_animationName );
                    pFrameCount = pAnimation->getFrames().size();
                }
                
                PhysicsComponent* pPhysicsComponent = EntitySystem::GetComponent<PhysicsComponent>( pComponent->m_entityHandle );
                if ( pPhysicsComponent )
                {
                    pPosition = pPhysicsComponent->GetPosition();
                }
                
                char pChar[200];
                sprintf( pChar, "%d", i );
                std::string pText = std::string( pChar );
                RenderSystem::DebugText( pText, pPosition, 0.001f, cocos2d::Color4F::RED, 16 );
                
                cocos2d::Vec2 pInfoPosition = cocos2d::Vec2( 1750.0f, 1010.0f - ( i * 20.0f ) );
                sprintf( pChar, "%d: %s - %s[%03d/%03d] %.0f%%", i, pMotionName.c_str(), pAnimationName.c_str(), pFrameIndex, pFrameCount, pAnimRate * 100.0f );
                pText = std::string( pChar );
                RenderSystem::DebugText( pText, pInfoPosition, 0.001f, cocos2d::Color4F::RED, 16 );
            }
#endif
        }
        i++;
    }
}