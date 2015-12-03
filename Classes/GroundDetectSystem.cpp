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
bool GroundDetectSystem::m_debug;

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
            bool pHit = false;
            cocos2d::Vec2 pPosition;
            cocos2d::Vec2 pEnd;
            cocos2d::Vec2 pHitPoint;
            PhysicsComponent* pPhysicsComponent = EntitySystem::GetComponent<PhysicsComponent>( pComponent->m_entityHandle );
            if ( pPhysicsComponent )
            {
                cocos2d::PhysicsRayCastInfo pInfo;
                
                for ( int i = -1; i <= 1; i++ )
                {
                    float pOffset = (float) i * 0.25f * pPhysicsComponent->GetWidth();
                    pPosition = pPhysicsComponent->GetPosition() + cocos2d::Vec2( pOffset, 1.0f );
                    pEnd = pPosition + cocos2d::Vec2( 0.0f, -9.0f );
                    
                    pHit = pPhysicsComponent->RayCast( pPosition, pEnd, pInfo );
                    
#ifdef DEBUG
                    if ( m_debug )
                    {
                        cocos2d::DrawNode* pDrawNode = cocos2d::DrawNode::create();
                        pDrawNode->drawSegment( pPosition, pEnd, 1, cocos2d::Color4F::RED );
                        if ( pHit )
                        {
                            pDrawNode->drawPoint( pHitPoint, 3.0f, cocos2d::Color4F::GREEN );
                        }
                        RenderSystem::DebugDraw( pDrawNode, 0.0001f );
                    }
#endif
                    
                    if ( pHit )
                    {
                        pHitPoint = pInfo.contact;
                        break;
                    }
                }
            }
            
            if ( pHit != pComponent->GetOnGround() )
            {
                // OnGroundChange
                if ( pHit )
                {
                    AnimationComponent* pAnimationComponent = EntitySystem::GetComponent<AnimationComponent>( pComponent->m_entityHandle );
                    if ( pAnimationComponent )
                    {
                        pAnimationComponent->StartMotion( "Run", -1 );
                    }
                }
            }
            pComponent->SetOnGround( pHit );
        }
    }
}