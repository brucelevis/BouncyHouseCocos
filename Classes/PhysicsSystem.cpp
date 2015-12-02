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
std::map<std::string, CollisionCategory> PhysicsSystem::m_collisionCategoryMap;

void PhysicsSystem::RegisterComponent( Component* i_component )
{
    m_components.insert( std::make_pair( i_component->m_entityHandle, i_component ) );
}

void PhysicsSystem::UnregisterComponent( Component* i_component )
{
    m_components.erase( i_component->m_entityHandle );
}

void PhysicsSystem::Init()
{
    m_collisionCategoryMap.insert( std::make_pair( "None", CollisionCategory::None ) );
    m_collisionCategoryMap.insert( std::make_pair( "Ground", CollisionCategory::Ground ) );
    m_collisionCategoryMap.insert( std::make_pair( "Player", CollisionCategory::Player ) );
    m_collisionCategoryMap.insert( std::make_pair( "All", CollisionCategory::All ) );
}

void PhysicsSystem::Update( float i_dt )
{
    for ( std::map<EntityHandle, Component*>::iterator it = m_components.begin(); it != m_components.end(); it++ )
    {
        PhysicsComponent* pComponent = (PhysicsComponent*) it->second;
        if ( pComponent )
        {
//#ifdef DEBUG
//            cocos2d::DrawNode* pDrawNode = cocos2d::DrawNode::create();
//            pDrawNode->drawPoint( pComponent->GetPosition(), 10.0f, cocos2d::Color4F::GREEN );
//            RenderSystem::DebugDraw( pDrawNode, i_dt * 0.25f );
//#endif
            
            // Death plane at -100.0f y
            if ( pComponent->GetPosition().y < -100.0f )
            {
                EntitySystem::MarkForDelete( pComponent->m_entityHandle );
                continue;
            }
        }
    }
}

bool PhysicsSystem::SetPosition( EntityHandle i_entityHandle, cocos2d::Vec2 i_position )
{
    PhysicsComponent* pComponent = EntitySystem::GetComponent<PhysicsComponent>( i_entityHandle );
    if ( pComponent )
    {
        return pComponent->SetPosition( i_position );
    }
    return false;
}

CollisionCategory PhysicsSystem::GetCollisionCategory( std::string i_collisionCategory )
{
    for ( std::map<std::string, CollisionCategory>::iterator it = m_collisionCategoryMap.begin(); it != m_collisionCategoryMap.end(); it++ )
    {
        if ( strcmp( it->first.c_str(), i_collisionCategory.c_str() ) == 0 )
        {
            return it->second;
        }
    }
    char msg[100] = {0};
    sprintf( msg, "Collision Category '%s' not found", i_collisionCategory.c_str() );
    ASSERTS( false, msg );
    
    return CollisionCategory::None;
}

bool PhysicsSystem::OnContactBegin( cocos2d::PhysicsContact& i_contact )
{
//    cocos2d::PhysicsBody* bodyA = i_contact.getShapeA()->getBody();
//    cocos2d::PhysicsBody* bodyB = i_contact.getShapeB()->getBody();
//    
//    EntityHandle pEntityHandleA = bodyA->getNode()->getTag();
//    EntityHandle pEntityHandleB = bodyB->getNode()->getTag();
    
    return true;
}