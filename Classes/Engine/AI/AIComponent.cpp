//
//  AIComponent.cpp
//  BouncyHouse
//
//  Created by Derek Peterson on 1/15/16.
//
//

#include "AIComponent.h"
#include "AISystem.h"
#include "AIBrain/AIBrain.h"

std::string AIComponent::s_componentType = "AIComponent";

void AIComponent::DNADataInit( EntityHandle i_entityHandle, const rapidjson::Value& i_dnaObject )
{
    m_entityHandle = i_entityHandle;
    AISystem::GetInstance()->RegisterComponent( this );
    
    m_brain = new AIBrain( m_entityHandle );
    
    if ( i_dnaObject.HasMember("DefaultBrainState") )
    {
        std::string pBrainStateName = i_dnaObject["DefaultBrainState"].GetString();
        if ( m_brain )
        {
            m_brain->PushState( pBrainStateName );
        }
    }
}

AIComponent::~AIComponent()
{
    delete m_brain;
    AISystem::GetInstance()->UnregisterComponent( this );
}

void AIComponent::Update( float i_dt )
{
    if ( m_brain )
    {
        m_brain->Update( i_dt );
    }
}