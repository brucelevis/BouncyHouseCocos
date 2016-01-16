//
//  AISystem.cpp
//  BouncyHouse
//
//  Created by Derek Peterson on 1/15/16.
//
//

#include "AIComponent.h"
#include "AISystem.h"
#include "../Entity/EntitySystem.h"
#include "../Render/DebugDrawSystem.h"

AISystem* AISystem::s_instance;

AISystem* AISystem::GetInstance()
{
    if ( !s_instance )
    {
        s_instance = new AISystem();
    }
    return s_instance;
}

void AISystem::DestroyInstance()
{
    if ( s_instance )
    {
        delete s_instance;
        s_instance = NULL;
    }
}

void AISystem::RegisterComponent( Component* i_component )
{
    m_components.insert( std::make_pair( i_component->m_entityHandle, i_component ) );
}

void AISystem::UnregisterComponent( Component* i_component )
{
    m_components.erase( i_component->m_entityHandle );
}

void AISystem::Update( float i_dt )
{
    int i = 0;
    for ( std::map<EntityHandle, Component*>::iterator it = m_components.begin(); it != m_components.end(); it++ )
    {
        AIComponent* pComponent = (AIComponent*) it->second;
        if ( pComponent )
        {
            pComponent->Update( i_dt );
#ifdef DEBUG
            std::string pStateName;
            if ( m_debug && pComponent->GetBrain() && pComponent->GetBrain()->GetCurrentState() )
            {
                pStateName = pComponent->GetBrain()->GetCurrentState()->GetStateName();
                char pChar[200];
                cocos2d::Vec2 pInfoPosition = cocos2d::Vec2( 1600.0f, 1010.0f - ( i * 20.0f ) );
                sprintf( pChar, "%-10s (%06d): %s", EntitySystem::GetInstance()->GetEntity( pComponent->m_entityHandle )->GetName().c_str(), pComponent->m_entityHandle, pStateName.c_str() );
                std::string pText = std::string( pChar );
                DebugDrawSystem::GetInstance()->DebugText( pText, pInfoPosition, 0.0001f, cocos2d::Color4F::WHITE, 14, cocos2d::TextHAlignment::LEFT );
            }
#endif
        }
        i++;
    }
}

AIBrainState* AISystem::CreateBrainState( std::string i_stateName )
{
    AIBrainStateMap::iterator it = m_brainStateTypes.find( i_stateName );
    if ( it == m_brainStateTypes.end() )
        return NULL;
    
    AIBrainState* pState = it->second();
    pState->SetStateName( i_stateName );
    return pState;
}


