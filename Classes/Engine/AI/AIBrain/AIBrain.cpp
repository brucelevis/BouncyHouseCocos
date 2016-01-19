//
//  AIBrain.cpp
//  BouncyHouse
//
//  Created by Derek Peterson on 1/15/16.
//
//

#include "AIBrain.h"
#include "../AISystem.h"
#include "../../Entity/EntitySystem.h"

AIBrain::AIBrain( EntityHandle i_entityHandle )
{
    m_entityHandle = i_entityHandle;
    m_shouldPop = false;
    m_shouldPush = false;
}

AIBrain::~AIBrain()
{
    while ( m_states.size() > 0 )
    {
        AIBrainState* pState = m_states.top();
        if ( pState )
        {
            delete pState;
        }
        m_states.pop();
    }
}

void AIBrain::Update( float i_dt )
{
    if ( m_states.size() > 0 )
    {
        AIBrainState* pState = m_states.top();
        if ( pState )
        {
            pState->Update( i_dt );
        }
    }
    if ( m_shouldPop )
    {
        PerformPopState();
    }
    if ( m_shouldPush )
    {
        PerformPushState( m_pushStateName );
    }
}

void AIBrain::PopState()
{
    m_shouldPop = true;
    if ( m_states.size() > 0 )
    {
        AIBrainState* pState = m_states.top();
        if ( pState && pState->GetActive() )
        {
            pState->OnDeactivate();
        }
    }
}

void AIBrain::PushState( std::string i_stateName )
{
    if ( m_states.size() > 0 )
    {
        AIBrainState* pState = m_states.top();
        if ( pState && !pState->GetInterruptible() )
        {
            return;
        }
        if ( pState && strcmp( pState->GetStateName().c_str(), i_stateName.c_str() ) == 0 && !m_shouldPop )
        {
            //ASSERTS( false, "AIBrain: Tried to push same state on top of itself." );
            return;
        }
        if ( pState && pState->GetActive() )
        {
            pState->OnDeactivate();
        }
    }
    m_shouldPush = true;
    m_pushStateName = i_stateName;
}

void AIBrain::PerformPopState()
{
    if ( m_states.size() > 0 )
    {
        AIBrainState* pState = m_states.top();
        if ( pState )
        {
            pState->Exit();
            delete pState;
        }
        m_states.pop();
    }
    if ( m_states.size() > 0 )
    {
        AIBrainState* pState = m_states.top();
        if ( pState && !pState->GetActive() )
        {
            pState->OnActivate();
        }
    }
    m_shouldPop = false;
}

void AIBrain::PerformPushState( std::string i_stateName )
{
    if ( m_states.size() > 0 )
    {
        AIBrainState* pState = m_states.top();
        if ( pState && pState->GetActive() )
        {
            pState->OnDeactivate();
        }
    }
    AIBrainState* pState = AISystem::GetInstance()->CreateBrainState( i_stateName );
    ASSERTS( pState, "AIBrain state not found" );
    if ( pState )
    {
        pState->Init( m_entityHandle );
        pState->Enter();
        pState->OnActivate();
        m_states.push( pState );
    }
    m_shouldPush = false;
}

AIBrainState* AIBrain::GetCurrentState()
{
    if ( m_states.size() > 0 )
    {
        AIBrainState* pState = m_states.top();
        if ( pState)
        {
            return pState;
        }
    }
    return NULL;
}