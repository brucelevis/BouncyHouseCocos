//
//  PhysicsComponent.cpp
//  BouncyHouse
//
//  Created by Derek Peterson on 11/28/15.
//
//

#include "ComponentSystem.h"
#include "EntitySystem.h"
#include "PhysicsComponent.h"
#include "PhysicsSystem.h"
#include "RenderComponent.h"

using namespace cocos2d;

std::string PhysicsComponent::s_componentType = "PhysicsComponent";

void PhysicsComponent::Init( EntityHandle i_entityHandle, const rapidjson::Value& i_dnaObject )
{
    m_entityHandle = i_entityHandle;
    PhysicsSystem::RegisterComponent( this );
    
    RenderComponent* pRenderComponent = EntitySystem::GetComponent<RenderComponent>( m_entityHandle );
    if ( pRenderComponent && pRenderComponent->m_sprite )
    {
        m_node = pRenderComponent->m_sprite;
    }
    
    if ( m_node )
    {
        m_node->setAnchorPoint( cocos2d::Vec2( 0.5f, 0.0f ) );
        
        
        m_physicsBody = PhysicsBody::createBox( Size( pRenderComponent->m_sprite->getContentSize().width, pRenderComponent->m_sprite->getContentSize().height ), PhysicsMaterial( 0.1f, 1.0f, 0.0f ) );
        m_physicsBody->setDynamic( false );
        m_physicsBody->setMass( 10.0f );
        m_node->setPhysicsBody( m_physicsBody );
    }
}

PhysicsComponent::~PhysicsComponent()
{
    if ( m_physicsBody && m_physicsBody->getShapes().size() > 0 )
        m_physicsBody->removeAllShapes();
    if ( m_physicsBody && m_physicsBody->getWorld() )
        m_physicsBody->removeFromWorld();
    PhysicsSystem::UnregisterComponent( this );
}