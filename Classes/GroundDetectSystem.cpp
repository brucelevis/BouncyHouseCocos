//
//  GroundDetectSystem.cpp
//  BouncyHouse
//
//  Created by Derek Peterson on 12/2/15.
//
//

#include "AnimationComponent.h"
#include "RenderComponent.h"
#include "EntitySystem.h"
#include "GroundDetectComponent.h"
#include "GroundDetectSystem.h"
#include "PhysicsComponent.h"
#include "PhysicsSystem.h"
#include "RenderSystem.h"

std::map<EntityHandle, Component*> GroundDetectSystem::m_components;

void GroundDetectSystem::RegisterComponent( Component* i_component )
{
    m_components.insert( std::make_pair( i_component->m_entityHandle, i_component ) );
}

void GroundDetectSystem::UnregisterComponent( Component* i_component )
{
    m_components.erase( i_component->m_entityHandle );
}
void GroundDetectSystem::Update( float i_dt )
{
    for ( std::map<EntityHandle, Component*>::iterator it = m_components.begin(); it != m_components.end(); it++ )
    {
        GroundDetectComponent* pComponent = (GroundDetectComponent*) it->second;
        if ( pComponent )
        {
            cocos2d::Vec2 pPosition = cocos2d::Vec2::ZERO;
            PhysicsComponent* pPhysicsComponent = EntitySystem::GetComponent<PhysicsComponent>( pComponent->m_entityHandle );
            if ( pPhysicsComponent )
            {
                pPosition = pPhysicsComponent->GetPosition() + cocos2d::Vec2( 0.0f, 1.0f );
            }
            cocos2d::Vec2 pEnd = pPosition + cocos2d::Vec2( 0.0f, -9.0f );
            
            cocos2d::Vec2 pPoint;
            bool pHit = false;
            cocos2d::PhysicsRayCastCallbackFunc pFunc = [&pPoint, &pHit](cocos2d::PhysicsWorld& i_world, const cocos2d::PhysicsRayCastInfo& i_info, void* i_data )->bool
            {
                if ( PhysicsSystem::IsInBitmask( CollisionCategory::Ground, (CollisionCategory)i_info.shape->getBody()->getCategoryBitmask() ) )
                {
                    pPoint = i_info.contact;
                    pHit = true;
                }
                return true;
            };
            RenderSystem::m_activeScene->getPhysicsWorld()->rayCast( pFunc, pPosition, pEnd, nullptr );
            
            if ( pHit != pComponent->GetOnGround() )
            {
                // OnGroundChange
                if ( pHit )
                {
                    RenderComponent* pRenderComponent = EntitySystem::GetComponent<RenderComponent>( pComponent->m_entityHandle );
                    if ( pRenderComponent )
                    {
                        AnimationComponent* pAnimationComponent = EntitySystem::GetComponent<AnimationComponent>( pComponent->m_entityHandle );
                        if ( pAnimationComponent )
                        {
                            if ( pAnimationComponent->m_currentAnimation )
                            {
                                pRenderComponent->m_sprite->stopAction( pAnimationComponent->m_currentAnimation );
                            }
                        }
                        
                        cocos2d::Vector<cocos2d::SpriteFrame*> pFrames( 18 );
                        for ( int i = 0; i < 18; i++ )
                        {
                            char pFrameName[100] = {0};
                            sprintf( pFrameName, "Vik1_Run_%02d.png", i );
                            pFrames.pushBack( cocos2d::SpriteFrameCache::getInstance()->getSpriteFrameByName( pFrameName ) );
                        }
                        
                        auto animation = cocos2d::Animation::createWithSpriteFrames( pFrames, 1.0f / 30.0f );
                        animation->setLoops( -1 );
                        auto animate = cocos2d::Animate::create( animation );
                        pAnimationComponent->m_currentAnimation = pRenderComponent->m_sprite->runAction( animate );
                    }
                }
            }
            pComponent->SetOnGround( pHit );
            
//            cocos2d::DrawNode* pDrawNode = cocos2d::DrawNode::create();
//            pDrawNode->drawSegment( pPosition, pEnd, 1, cocos2d::Color4F::RED );
//            pDrawNode->drawPoint( pPoint, 3.0f, cocos2d::Color4F::GREEN );
//            RenderSystem::DebugDraw( pDrawNode, 1.0f );
        }
    }
}