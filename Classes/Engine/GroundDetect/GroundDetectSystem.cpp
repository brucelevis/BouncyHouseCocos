//
//  GroundDetectSystem.cpp
//  BouncyHouse
//
//  Created by Derek Peterson on 12/2/15.
//
//

#include "../Animation/AnimationComponent.h"
#include "../Render/RenderComponent.h"
#include "../Entity/EntitySystem.h"
#include "../Event/EventManager.h"
#include "GroundDetectComponent.h"
#include "GroundDetectSystem.h"
#include "../Physics/PhysicsComponent.h"
#include "../Physics/PhysicsSystem.h"
#include "../Render/DebugDrawSystem.h"

GroundDetectSystem* GroundDetectSystem::s_instance;

GroundDetectSystem* GroundDetectSystem::GetInstance()
{
    if ( !s_instance )
    {
        s_instance = new GroundDetectSystem();
    }
    return s_instance;
}

void GroundDetectSystem::DestroyInstance()
{
    if ( s_instance )
    {
        delete s_instance;
        s_instance = NULL;
    }
}

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
            PhysicsComponent* pPhysicsComponent = EntitySystem::GetInstance()->GetComponent<PhysicsComponent>( pComponent->m_entityHandle );
            if ( pPhysicsComponent )
            {
                cocos2d::PhysicsRayCastInfo pInfo;
                
                for ( int i = -1; i <= 1; i++ )
                {
                    float pOffset = (float) i * 0.25f * pPhysicsComponent->GetWidth() * fabs( pPhysicsComponent->GetNode()->getScaleX() );
                    pPosition = pPhysicsComponent->GetPosition() + cocos2d::Vec2( pOffset, 1.0f );
                    pEnd = pPosition + cocos2d::Vec2( 0.0f, -14.0f * pPhysicsComponent->GetNode()->getScaleY() );
                    
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
                        DebugDrawSystem::GetInstance()->DebugDraw( pDrawNode, 0.0001f );
                    }
#endif
                    
                    if ( pHit )
                    {
                        pHitPoint = pInfo.contact;
                        break;
                    }
                }
            }
            
            bool pOldOnGround = pComponent->GetOnGround();
            pComponent->SetOnGround( pHit );
            if ( pHit != pOldOnGround )
            {
                // OnGroundChanged
                if ( pHit )
                {
                    EventManager::GetInstance()->SendEvent( "GroundChanged", &pComponent->m_entityHandle );
                }
            }
        }
    }
}
