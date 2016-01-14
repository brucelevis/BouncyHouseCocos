//
//  PhysicsComponent.cpp
//  BouncyHouse
//
//  Created by Derek Peterson on 11/28/15.
//
//

#include "cocos2d.h"

#include "../Entity/ComponentSystem.h"
#include "../Entity/DNASequencer.h"
#include "../Entity/EntitySystem.h"
#include "../Event/EventManager.h"
#include "PhysicsComponent.h"
#include "PhysicsSystem.h"
#include "../Render/RenderComponent.h"
#include "../Render/RenderSystem.h"

std::string PhysicsComponent::s_componentType = "PhysicsComponent";

void PhysicsComponent::DNADataInit( EntityHandle i_entityHandle, const rapidjson::Value& i_dnaObject )
{
    m_entityHandle = i_entityHandle;
    PhysicsSystem::RegisterComponent( this );
//    m_node = NULL;
//    m_physicsBody = NULL;
    
    m_width = 0.0f;
    m_height = 0.0f;
    m_density = 0.0f;
    m_restitution = 0.0f;
    m_friction = 0.0f;
    m_category = CollisionCategory::None;
    m_collision = CollisionCategory::None;
    m_contact = CollisionCategory::None;
    
    if ( i_dnaObject.HasMember( "AnchorPoint" ) )
    {
        m_anchorPoint = cocos2d::Vec2( i_dnaObject["AnchorPoint"][0].GetDouble(), i_dnaObject["AnchorPoint"][1].GetDouble() );
    }
    if ( i_dnaObject.HasMember( "YOffset" ) )
    {
        m_offset = cocos2d::Vec2( 0.0f, i_dnaObject["YOffset"].GetDouble() );
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
        m_restitution = i_dnaObject["Restitution"].GetDouble();
    }
    if ( i_dnaObject.HasMember( "Friction" ) )
    {
        m_friction = i_dnaObject["Friction"].GetDouble();
    }
    if ( i_dnaObject.HasMember( "Dynamic" ) )
    {
        m_dynamic = i_dnaObject["Dynamic"].GetBool();
    }
    if ( i_dnaObject.HasMember( "Category" ) )
    {
        m_category = (CollisionCategory) DNASequencer::CreateCollisionCategory( i_dnaObject["Category"] );
    }
    if ( i_dnaObject.HasMember( "Collision" ) )
    {
        m_collision = (CollisionCategory) DNASequencer::CreateCollisionCategory( i_dnaObject["Collision"] );
    }
    if ( i_dnaObject.HasMember( "Contact" ) )
    {
        m_contact = (CollisionCategory) DNASequencer::CreateCollisionCategory( i_dnaObject["Contact"] );
    }
}

void PhysicsComponent::OnActivate()
{
    RenderComponent* pRenderComponent = EntitySystem::GetComponent<RenderComponent>( m_entityHandle );
    if ( pRenderComponent && pRenderComponent->m_sprite )
    {
        m_node = pRenderComponent->m_sprite;
    }
    else
    {
        m_node = cocos2d::Node::create();
        m_node->setTag( m_entityHandle );
        RenderSystem::GetInstance()->GetScene()->addChild( m_node );
    }
        
    if ( m_node )
    {
        m_node->setAnchorPoint( m_anchorPoint );
        
        if ( m_width != 0.0f && m_height != 0.0f )
        {
            m_physicsBody = cocos2d::PhysicsBody::createBox( cocos2d::Size( m_width, m_height ), cocos2d::PhysicsMaterial( m_density, m_restitution, m_friction ) );
            m_physicsBody->setPositionOffset( m_offset );
            m_physicsBody->setDynamic( m_dynamic );
            m_physicsBody->setMass( 10.0f );
            m_physicsBody->setRotationEnable( false );
            
            m_physicsBody->setCategoryBitmask( m_category );
            m_physicsBody->setCollisionBitmask( m_collision );
            m_physicsBody->setContactTestBitmask( m_contact );
            
            m_node->setPhysicsBody( m_physicsBody );
        }
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
    ASSERTS( m_node, "Missing node!" );
    if ( m_node )
    {
#ifdef DEBUG_NAN
        ASSERTS( !isnan( i_position.x ), "NaN entering PhysicsSystem!" );
        ASSERTS( !isnan( i_position.y ), "NaN entering PhysicsSystem!" );
#endif
        m_node->setPosition( i_position );
        return true;
    }
    return false;
}

bool PhysicsComponent::SetVelocity( cocos2d::Vec2 i_velocity )
{
    if ( m_node )
    {
#ifdef DEBUG_NAN
        ASSERTS( !isnan( i_velocity.x ), "NaN entering PhysicsSystem!" );
        ASSERTS( !isnan( i_velocity.y ), "NaN entering PhysicsSystem!" );
#endif
        m_physicsBody->setVelocity( i_velocity );
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
#ifdef DEBUG_NAN
        ASSERTS( !isnan( i_impulse.x ), "NaN entering PhysicsSystem!" );
        ASSERTS( !isnan( i_impulse.y ), "NaN entering PhysicsSystem!" );
#endif
        m_physicsBody->applyImpulse( i_impulse );
    }
}

bool PhysicsComponent::RayCast( cocos2d::Vec2 i_start, cocos2d::Vec2 i_end, cocos2d::PhysicsRayCastInfo& o_info )
{
    EntityHandle pEntityHandle = m_entityHandle;
    CollisionCategory pCollisionMask = GetCollisionMask();
    bool pHit = false;
    cocos2d::PhysicsRayCastCallbackFunc pFunc = [&pHit, &pEntityHandle, &pCollisionMask, &o_info](cocos2d::PhysicsWorld& i_world, const cocos2d::PhysicsRayCastInfo& i_info, void* i_data )->bool
    {
        if ( pHit == false )
        {
            if ( i_info.shape->getBody()->getNode()->getTag() != pEntityHandle && PhysicsSystem::IsInBitmask( pCollisionMask  , (CollisionCategory)i_info.shape->getBody()->getCategoryBitmask() ) )
            {
                pHit = true;
                o_info.start = i_info.start;
                o_info.end = i_info.end;
                o_info.shape = i_info.shape;
                o_info.contact = i_info.contact;
                o_info.normal = i_info.normal;
            }
        }
        return true;
    };
    RenderSystem::GetInstance()->GetScene()->getPhysicsWorld()->rayCast( pFunc, i_start, i_end, nullptr );

    return pHit;
}

bool PhysicsComponent::OnContactBegin( PhysicsContactInfo i_contact )
{
    EventManager::GetInstance()->SendEvent( "PhysicsContactBegin", &i_contact );
    return true;
}

void PhysicsComponent::OnContactPostSolve( PhysicsContactInfo i_contact )
{
    EventManager::GetInstance()->SendEvent( "PhysicsContactPostSolve", &i_contact );
}
