//
//  PhysicsComponent.cpp
//  BouncyHouse
//
//  Created by Derek Peterson on 11/28/15.
//
//

#include "ComponentSystem.h"
#include "DNASequencer.h"
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
    
    if ( i_dnaObject.HasMember( "AnchorPoint" ) )
    {
        m_anchorPoint = cocos2d::Vec2( i_dnaObject["AnchorPoint"][0].GetDouble(), i_dnaObject["AnchorPoint"][1].GetDouble() );
    }
    if ( i_dnaObject.HasMember( "Size" ) )
    {
        m_width = i_dnaObject["Size"][0].GetDouble();
        m_height = i_dnaObject["Size"][1].GetDouble();
    }
    if ( i_dnaObject.HasMember( "Density" ) )
    {
        m_density = i_dnaObject["Density"].GetDouble();
    }
    if ( i_dnaObject.HasMember( "Restitution" ) )
    {
        m_density = i_dnaObject["Restitution"].GetDouble();
    }
    if ( i_dnaObject.HasMember( "Friction" ) )
    {
        m_density = i_dnaObject["Friction"].GetDouble();
    }
    if ( i_dnaObject.HasMember( "Dynamic" ) )
    {
        m_dynamic = i_dnaObject["Dynamic"].GetBool();
    }
    if ( i_dnaObject.HasMember( "Category" ) )
    {
        m_category = DNASequencer::CreateCollisionCategory( i_dnaObject["Category"] );
    }
    if ( i_dnaObject.HasMember( "Collision" ) )
    {
        m_collision = DNASequencer::CreateCollisionCategory( i_dnaObject["Collision"] );
    }
    if ( i_dnaObject.HasMember( "Contact" ) )
    {
        m_contact = DNASequencer::CreateCollisionCategory( i_dnaObject["Contact"] );
    }
    
    
    RenderComponent* pRenderComponent = EntitySystem::GetComponent<RenderComponent>( m_entityHandle );
    if ( pRenderComponent && pRenderComponent->m_sprite )
    {
        m_node = pRenderComponent->m_sprite;
    }
    
    if ( m_node )
    {
        m_node->setAnchorPoint( m_anchorPoint );
        m_node->setPosition( cocos2d::Vec2( 0.0f, 0.0f ) );
        
        m_physicsBody = PhysicsBody::createBox( Size( m_width, m_height ), PhysicsMaterial( m_density, m_restitution, m_friction ) );
        m_physicsBody->setDynamic( m_dynamic );
        m_physicsBody->setMass( 10.0f );
        m_physicsBody->setRotationEnable( false );
        
        m_physicsBody->setCategoryBitmask( m_category );
        m_physicsBody->setCollisionBitmask( m_collision );
        m_physicsBody->setContactTestBitmask( m_contact );
        
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