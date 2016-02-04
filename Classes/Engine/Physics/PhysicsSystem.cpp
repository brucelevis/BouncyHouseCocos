//
//  PhysicsSystem.cpp
//  BouncyHouse
//
//  Created by Derek Peterson on 11/28/15.
//
//

#include <cmath>

#include "cocos2d.h"

#include "../Entity/EntitySystem.h"
#include "../Event/EventManager.h"
#include "PhysicsSystem.h"
#include "PhysicsComponent.h"
#include "../Render/DebugDrawSystem.h"
#include "../Render/RenderSystem.h"

PhysicsSystem* PhysicsSystem::s_instance;

PhysicsSystem* PhysicsSystem::GetInstance()
{
    if ( !s_instance )
    {
        s_instance = new PhysicsSystem();
    }
    return s_instance;
}

void PhysicsSystem::DestroyInstance()
{
    if ( s_instance )
    {
        delete s_instance;
        s_instance = NULL;
    }
}

void PhysicsSystem::RegisterComponent( Component* i_component )
{
    m_components.insert( std::make_pair( i_component->m_entityHandle, i_component ) );
}

void PhysicsSystem::UnregisterComponent( Component* i_component )
{
    m_components.erase( i_component->m_entityHandle );
}

void PhysicsSystem::DNADataInit()
{
    m_collisionCategoryMap.insert( std::make_pair( "None", CollisionCategory::None ) );
    m_collisionCategoryMap.insert( std::make_pair( "Environment", CollisionCategory::Environment ) );
    m_collisionCategoryMap.insert( std::make_pair( "Solid", CollisionCategory::Solid ) );
    m_collisionCategoryMap.insert( std::make_pair( "Player", CollisionCategory::Player ) );
    m_collisionCategoryMap.insert( std::make_pair( "Enemy", CollisionCategory::Enemy ) );
    m_collisionCategoryMap.insert( std::make_pair( "Bouncy", CollisionCategory::Bouncy ) );
    m_collisionCategoryMap.insert( std::make_pair( "Munition", CollisionCategory::Munition ) );
    m_collisionCategoryMap.insert( std::make_pair( "Damagable", CollisionCategory::Damagable ) );
    m_collisionCategoryMap.insert( std::make_pair( "Ground", CollisionCategory::Ground ) );
    m_collisionCategoryMap.insert( std::make_pair( "All", CollisionCategory::All ) );
    
    m_deathPlaneTimer = 0.0f;
}

void PhysicsSystem::Update( float i_dt )
{
    GetPhysicsWorld()->step( i_dt * 0.25f );
    GetPhysicsWorld()->step( i_dt * 0.25f );
    GetPhysicsWorld()->step( i_dt * 0.25f );
    GetPhysicsWorld()->step( i_dt * 0.25f );
#ifdef DEBUG
    if ( m_debug )
    {
        for ( std::map<EntityHandle, Component*>::iterator it = m_components.begin(); it != m_components.end(); it++ )
        {
            PhysicsComponent* pComponent = (PhysicsComponent*) it->second;
            if ( pComponent )
            {
                cocos2d::DrawNode* pDrawNode = cocos2d::DrawNode::create();
                pDrawNode->drawPoint( pComponent->GetPosition(), 10.0f, cocos2d::Color4F::BLUE );
                DebugDrawSystem::GetInstance()->DebugDraw( pDrawNode, i_dt * 0.25f );
            }
        }
    }
#endif
    m_deathPlaneTimer -= i_dt;
    if ( m_deathPlaneTimer < 0.0f )
    {
        for ( std::map<EntityHandle, Component*>::iterator it = m_components.begin(); it != m_components.end(); it++ )
        {
            PhysicsComponent* pComponent = (PhysicsComponent*) it->second;
            if ( pComponent )
            {
                // Death plane at -100.0f y
                if ( pComponent->GetPosition().y < -100.0f )
                {
#ifdef DEBUG
                    //ASSERTS( false, "Entity below death plane!" );
                    printf( "Entity below death plane: %s\n", EntitySystem::GetInstance()->GetNameDoNotUseInCode( pComponent->m_entityHandle ).c_str() );
#endif
                    EntitySystem::GetInstance()->MarkForDelete( pComponent->m_entityHandle );
                    continue;
                }
            }
        }
        m_deathPlaneTimer = 1.0f;
    }
}

bool PhysicsSystem::SetPosition( EntityHandle i_entityHandle, cocos2d::Vec2 i_position
                                )
{
    PhysicsComponent* pComponent = EntitySystem::GetInstance()->GetComponent<PhysicsComponent>( i_entityHandle );
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

bool PhysicsSystem::IsInBitmask( CollisionCategory i_collisionCategory, CollisionCategory i_mask )
{
    return ( i_mask & i_collisionCategory ) > 0;
}

bool PhysicsSystem::OnContactBegin( cocos2d::PhysicsContact& i_contact )
{
    EntityHandle pEntityHandleA = i_contact.getShapeA()->getBody()->getNode()->getTag();
    EntityHandle pEntityHandleB = i_contact.getShapeB()->getBody()->getNode()->getTag();
    
    PhysicsContactInfo pContactA = PhysicsContactInfo( pEntityHandleA, pEntityHandleB, i_contact.getShapeA(), i_contact.getShapeB(), i_contact.getContactData()->normal );
    PhysicsContactInfo pContactB = PhysicsContactInfo( pEntityHandleB, pEntityHandleA, i_contact.getShapeB(), i_contact.getShapeA(), i_contact.getContactData()->normal * -1.0f );
    
    EventManager::GetInstance()->SendEvent( "PhysicsContactBegin", &pContactA );
    EventManager::GetInstance()->SendEvent( "PhysicsContactBegin", &pContactB );
    
    return true;
}

bool PhysicsSystem::OnContactPostSolve( cocos2d::PhysicsContact& i_contact )
{
    EntityHandle pEntityHandleA = i_contact.getShapeA()->getBody()->getNode()->getTag();
    EntityHandle pEntityHandleB = i_contact.getShapeB()->getBody()->getNode()->getTag();
    
    PhysicsContactInfo pContactA = PhysicsContactInfo( pEntityHandleA, pEntityHandleB, i_contact.getShapeA(), i_contact.getShapeB(), i_contact.getContactData()->normal );
    PhysicsContactInfo pContactB = PhysicsContactInfo( pEntityHandleB, pEntityHandleA, i_contact.getShapeB(), i_contact.getShapeA(), i_contact.getContactData()->normal * -1.0f );
    
    EventManager::GetInstance()->SendEvent( "PhysicsContactPostSolve", &pContactA );
    EventManager::GetInstance()->SendEvent( "PhysicsContactPostSolve", &pContactB );
    
    return true;
}
