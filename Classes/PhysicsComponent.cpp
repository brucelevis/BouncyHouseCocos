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
        m_node->setAnchorPoint( cocos2d::Vec2( i_dnaObject["AnchorPoint"][0].GetDouble(), i_dnaObject["AnchorPoint"][1].GetDouble() ) );
        m_node->setPosition( cocos2d::Vec2( 0.0f, 0.0f ) );
        
        m_physicsBody = PhysicsBody::createBox( Size( i_dnaObject["Size"][0].GetDouble(), i_dnaObject["Size"][1].GetDouble() ), PhysicsMaterial( i_dnaObject["Density"].GetDouble(), i_dnaObject["Restitution"].GetDouble(), i_dnaObject["Friction"].GetDouble() ) );
        m_physicsBody->setDynamic( i_dnaObject["Dynamic"].GetBool() );
        m_physicsBody->setMass( 10.0f );
        m_physicsBody->setRotationEnable( false );
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

cocos2d::Vec2 PhysicsComponent::GetPosition()
{
    if ( m_node )
    {
        return m_node->getPosition();
    }
    else
    {
        return cocos2d::Vec2::ZERO;
    }
}

bool PhysicsComponent::SetPosition( cocos2d::Vec2 i_position )
{
    if ( m_node )
    {
        m_node->setPosition( i_position );
        return true;
    }
    return false;
}

cocos2d::Vec2 PhysicsComponent::GetVelocity()
{
    if ( m_physicsBody )
    {
        return m_physicsBody->getVelocity();
    }
    else
    {
        return cocos2d::Vec2::ZERO;
    }
}

void PhysicsComponent::ApplyImpulse( cocos2d::Vec2 i_impulse )
{
    if ( m_physicsBody )
    {
        m_physicsBody->applyImpulse( i_impulse );
    }
}