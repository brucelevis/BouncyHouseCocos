//
//  PhysicsSystem.cpp
//  BouncyHouse
//
//  Created by Derek Peterson on 11/28/15.
//
//

#include <cmath>

#include "EntitySystem.h"
#include "PhysicsSystem.h"
#include "PhysicsComponent.h"
#include "RenderSystem.h"

std::map<EntityHandle, Component*> PhysicsSystem::m_components;

void PhysicsSystem::RegisterComponent( Component* i_component )
{
    m_components.insert( std::make_pair( i_component->m_entityHandle, i_component ) );
}

void PhysicsSystem::UnregisterComponent( Component* i_component )
{
    m_components.erase( i_component->m_entityHandle );
}

void PhysicsSystem::Update( float i_dt )
{
    for ( std::map<EntityHandle, Component*>::iterator it = m_components.begin(); it != m_components.end(); it++ )
    {
        PhysicsComponent* pComponent = (PhysicsComponent*) it->second;
        if ( pComponent && pComponent->m_physicsBody )
        {
#ifdef DEBUG
            cocos2d::DrawNode* pDrawNode = cocos2d::DrawNode::create();
            pDrawNode->drawPoint( pComponent->m_node->getPosition(), 10.0f, cocos2d::Color4F::GREEN );
            RenderSystem::DebugDraw( pDrawNode, i_dt * 0.25f );
#endif
            
            
            if ( pComponent->m_physicsBody->getPosition().y < -100.0f )
            {
                EntitySystem::MarkForDelete( pComponent->m_entityHandle );
                continue;
            }
            
            cocos2d::Vec2 pVelocity = pComponent->m_physicsBody->getVelocity();
            float xDir = 1.0f;
            if ( pVelocity.x < 0.0f )
                xDir = -1.0f;
            float pImpulseAmount = ( 600.0f - fabs( pVelocity.x ) ) * xDir;
            cocos2d::Vec2 pImpulse = cocos2d::Vec2( pImpulseAmount, 0.0f );
            pComponent->m_physicsBody->applyImpulse( pImpulse );
        }
    }
}

bool PhysicsSystem::SetPosition( EntityHandle i_entityHandle, cocos2d::Vec2 i_position )
{
    PhysicsComponent* pComponent = EntitySystem::GetComponent<PhysicsComponent>( i_entityHandle );
    if ( pComponent && pComponent->m_node )
    {
        pComponent->m_node->setPosition( i_position );
        return true;
    }
    return false;
}