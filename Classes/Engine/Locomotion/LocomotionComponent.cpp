//
//  LocomotionComponent.cpp
//  BouncyHouse
//
//  Created by Derek Peterson on 12/1/15.
//
//

#include "LocomotionComponent.h"
#include "LocomotionSystem.h"
#include "../Render/RenderSystem.h"

std::string LocomotionComponent::s_componentType = "LocomotionComponent";

void LocomotionComponent::Init( EntityHandle i_entityHandle, const rapidjson::Value& i_dnaObject )
{
    m_entityHandle = i_entityHandle;
    m_jumpState = JumpState::NOT_JUMPING;
    
    if ( i_dnaObject.HasMember( "RunSpeed" ) )
    {
        m_runSpeed = i_dnaObject["RunSpeed"].GetDouble();
    }
    
    if ( i_dnaObject.HasMember( "WalkSpeed" ) )
    {
        m_walkSpeed = i_dnaObject["WalkSpeed"].GetDouble();
    }
    
    if ( i_dnaObject.HasMember( "LocomotionMode" ) )
    {
        m_locomotionModeName = i_dnaObject["LocomotionMode"].GetString();
    }
}

LocomotionComponent::~LocomotionComponent()
{
    
}

void LocomotionComponent::OnActivate()
{
    LocomotionSystem::RegisterComponent( this );
    
    m_locomotionMode = LocomotionSystem::CreateLocomotionMode( m_locomotionModeName );
    if ( m_locomotionMode )
    {
        m_locomotionMode->Init( m_entityHandle );
    }
}

void LocomotionComponent::OnDeactivate()
{
    if ( m_locomotionMode )
    {
        delete m_locomotionMode;
        m_locomotionMode = NULL;
    }
    
    LocomotionSystem::UnregisterComponent( this );
}
