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

void LocomotionComponent::DNADataInit( EntityHandle i_entityHandle, const rapidjson::Value& i_dnaObject )
{
    m_entityHandle = i_entityHandle;
    m_jumpState = JumpState::NOT_JUMPING;
    m_locomotionMode = NULL;
    
    if ( i_dnaObject.HasMember( "RunSpeed" ) )
    {
        m_runSpeed = i_dnaObject["RunSpeed"].GetDouble();
    }
    
    if ( i_dnaObject.HasMember( "WalkSpeed" ) )
    {
        m_walkSpeed = i_dnaObject["WalkSpeed"].GetDouble();
    }
}

LocomotionComponent::~LocomotionComponent()
{
    
}

void LocomotionComponent::OnActivate()
{
    LocomotionSystem::GetInstance()->RegisterComponent( this );
}

void LocomotionComponent::OnDeactivate()
{
    if ( m_locomotionMode )
    {
        delete m_locomotionMode;
        m_locomotionMode = NULL;
    }
    
    LocomotionSystem::GetInstance()->UnregisterComponent( this );
}

void LocomotionComponent::SetLocomotionMode( std::string i_locomotionModeName )
{
    if ( m_locomotionMode )
    {
        delete m_locomotionMode;
    }

    m_locomotionMode = LocomotionSystem::GetInstance()->CreateLocomotionMode( i_locomotionModeName );
    if ( m_locomotionMode )
    {
        m_locomotionMode->Init( m_entityHandle );
    }
}
