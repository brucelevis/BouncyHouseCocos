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
    PhysicsSystem::GetInstance()->RegisterComponent( this );
//    m_node = NULL;
//    m_physicsBody = NULL;
    
    m_mass = 1.0f;
    m_width = 0.0f;
    m_height = 0.0f;
    m_density = 0.0f;
    m_restitution = 0.0f;
    m_friction = 0.0f;
    m_scale = 1.0f;
    m_category = CollisionCategory::None;
    m_collision = CollisionCategory::None;
    m_contact = CollisionCategory::None;
    
    if ( i_dnaObject.HasMember( "AnchorPoint" ) )
    {
        m_anchorPoint = cocos2d::Vec2( i_dnaObject["AnchorPoint"][0].GetDouble(), i_dnaObject["AnchorPoint"][1].GetDouble() );
    }
    if ( i_dnaObject.HasMember( "Offset" ) )
    {
        m_offset = cocos2d::Vec2( i_dnaObject["Offset"][0].GetDouble(), i_dnaObject["Offset"][1].GetDouble() );
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
    if ( i_dnaObject.HasMember( "Scale" ) )
    {
        m_scale = i_dnaObject["Scale"].GetDouble();
    }
}

void PhysicsComponent::OnActivate()
{
    m_node = cocos2d::Node::create();
    m_node->setTag( m_entityHandle );
    m_node->setScale( m_scale );
    m_node->setVisible( true );
    RenderSystem::GetInstance()->GetScene()->addChild( m_node );
    m_node->setContentSize( cocos2d::Size( m_width, m_height ) );
    
    if ( m_width != 0.0f && m_height != 0.0f )
    {
        m_physicsBody = cocos2d::PhysicsBody::createBox( cocos2d::Size( m_width, m_height ), cocos2d::PhysicsMaterial( m_density, m_restitution, m_friction ) );
        m_physicsBody->setPositionOffset( m_offset );
        m_physicsBody->setDynamic( m_dynamic );
        m_physicsBody->setMass( m_mass );
        m_physicsBody->setRotationEnable( false );
        
        m_physicsBody->setCategoryBitmask( m_category );
        m_physicsBody->setCollisionBitmask( m_collision );
        m_physicsBody->setContactTestBitmask( m_contact );
        
        m_node->setPhysicsBody( m_physicsBody );
    }
    m_node->setAnchorPoint( m_anchorPoint );
    
    SetFacing( PhysicsComponent::FacingDirection::LEFT );
}

void PhysicsComponent::OnDeactivate()
{
    if ( m_physicsBody && m_physicsBody->getShapes().size() > 0 )
        m_physicsBody->removeAllShapes();
    if ( m_physicsBody && m_physicsBody->getWorld() )
        m_physicsBody->removeFromWorld();
}

PhysicsComponent::~PhysicsComponent()
{
    PhysicsSystem::GetInstance()->UnregisterComponent( this );
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

void PhysicsComponent::SetScale( float i_scale )
{
    RenderComponent* pRenderComponent = EntitySystem::GetInstance()->GetComponent<RenderComponent>( m_entityHandle );
    if ( pRenderComponent )
    {
        pRenderComponent->SetScale( i_scale );
    }
    else
    {
        m_scale = i_scale;
        if ( m_node )
        {
            m_node->setScale( m_scale );
        }
    }
}

float PhysicsComponent::GetScale()
{
    RenderComponent* pRenderComponent = EntitySystem::GetInstance()->GetComponent<RenderComponent>( m_entityHandle );
    if ( pRenderComponent )
    {
        return pRenderComponent->GetScale();
    }
    return m_scale;
}

cocos2d::Vec2 PhysicsComponent::GetPositionOffset()
{
    if ( m_physicsBody )
    {
        return m_physicsBody->getPositionOffset();
    }
    return cocos2d::Vec2::ZERO;
}

cocos2d::Vec2 PhysicsComponent::GetDefaultPositionOffset()
{
    return m_offset;
}

cocos2d::Vec2 PhysicsComponent::GetGravity()
{
    return PhysicsSystem::GetInstance()->GetPhysicsWorld()->getGravity();
}

void PhysicsComponent::SetPositionOffset( cocos2d::Vec2 i_offset )
{
    if ( m_physicsBody )
    {
        m_physicsBody->setPositionOffset( i_offset );
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
            if ( i_info.shape->getBody()->getNode()->getTag() != pEntityHandle && PhysicsSystem::GetInstance()->IsInBitmask( pCollisionMask  , (CollisionCategory)i_info.shape->getBody()->getCategoryBitmask() ) )
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

void PhysicsComponent::DisableCollision() {
    if ( m_physicsBody )
    {
        m_physicsBody->setCategoryBitmask( CollisionCategory::None );
        m_physicsBody->setCollisionBitmask( CollisionCategory::None );
        m_physicsBody->setContactTestBitmask( CollisionCategory::None );
    }
}

void PhysicsComponent::SetCategoryMask( CollisionCategory i_category )
{
    m_category = i_category;
    if ( m_physicsBody )
    {
        m_physicsBody->setCategoryBitmask( m_category );
    }
}

void PhysicsComponent::SetCollisionMask( CollisionCategory i_collision )
{
    m_collision = i_collision;
    if ( m_physicsBody )
    {
        m_physicsBody->setCollisionBitmask( m_collision );
    }
}

void PhysicsComponent::SetContactMask( CollisionCategory i_contact )
{
    m_contact = i_contact;
    if ( m_physicsBody )
    {
        m_physicsBody->setContactTestBitmask( m_contact );
    }
}

PhysicsComponent::FacingDirection PhysicsComponent::GetFacing()
{
    FacingDirection pFacing = FacingDirection::NONE;
    if ( m_node )
    {
        float pScaleX = m_node->getScaleX();
        if ( pScaleX < 0.0f )
        {
            return FacingDirection::LEFT;
        }
        else if ( pScaleX > 0.0f )
        {
            return FacingDirection::RIGHT;
        }
    }
    return pFacing;
}

bool PhysicsComponent::SetFacing( FacingDirection i_facingDirection )
{
    float pScaleX = m_node->getScaleX();
    switch ( i_facingDirection )
    {
        case FacingDirection::LEFT:
            pScaleX = -1.0f * fabs( pScaleX );
            break;
        case FacingDirection::RIGHT:
            pScaleX = 1.0f * fabs( pScaleX );
            break;
        default:
            break;
    }
    if ( m_node )
    {
        if ( m_node->getScaleX() != pScaleX )
        {
#ifdef DEBUG_NAN
            ASSERTS( !isnan( pScaleX ), "NaN entering RenderSystem!" );
#endif
            m_node->setScaleX( pScaleX );
            EventManager::GetInstance()->SendEvent( "FacingChanged", &m_entityHandle );
        }
        return true;
    }
    return false;
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
