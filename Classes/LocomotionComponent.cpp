//
//  LocomotionComponent.cpp
//  BouncyHouse
//
//  Created by Derek Peterson on 12/1/15.
//
//

#include "LocomotionComponent.h"
#include "LocomotionSystem.h"

using namespace cocos2d;

std::string LocomotionComponent::s_componentType = "LocomotionComponent";

void LocomotionComponent::Init( EntityHandle i_entityHandle, const rapidjson::Value& i_dnaObject )
{
    m_entityHandle = i_entityHandle;
    LocomotionSystem::RegisterComponent( this );
    
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
        m_locomotionMode = LocomotionSystem::CreateLocomotionMode( i_dnaObject["LocomotionMode"].GetString() );
        m_locomotionMode->Init( m_entityHandle );
    }
}

LocomotionComponent::~LocomotionComponent()
{
    if ( m_locomotionMode )
    {
        delete m_locomotionMode;
    }
    LocomotionSystem::UnregisterComponent( this );
}