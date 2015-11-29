//
//  PhysicsComponent.cpp
//  BouncyHouse
//
//  Created by Derek Peterson on 11/28/15.
//
//

#include "EntitySystem.h"
#include "PhysicsComponent.h"
#include "PhysicsSystem.h"
#include "RenderComponent.h"

using namespace cocos2d;

std::string PhysicsComponent::s_componentType = "PhysicsComponent";

PhysicsComponent::PhysicsComponent( EntityHandle i_entityHandle )
{
    m_entityHandle = i_entityHandle;
    
    PhysicsSystem::RegisterComponent( this );
}

void PhysicsComponent::Init()
{
    RenderComponent* pRenderComponent = EntitySystem::GetComponent<RenderComponent>( m_entityHandle );
    if ( pRenderComponent && pRenderComponent->m_sprite )
    {
        m_physicsBody = PhysicsBody::createBox( Size( pRenderComponent->m_sprite->getContentSize().width, pRenderComponent->m_sprite->getContentSize().height ), PhysicsMaterial( 0.1f, 1.0f, 0.0f ) );
        m_physicsBody->setDynamic( true );
        m_physicsBody->setMass( 10.0f );
        
        pRenderComponent->m_sprite->setPhysicsBody( m_physicsBody );
    }
}

PhysicsComponent::~PhysicsComponent()
{
    m_physicsBody->removeAllShapes();
    m_physicsBody->removeFromWorld();
    PhysicsSystem::UnregisterComponent( this );
}