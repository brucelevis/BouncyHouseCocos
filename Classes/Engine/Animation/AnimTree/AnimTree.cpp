//
//  AnimTree.cpp
//  BouncyHouse
//
//  Created by Derek Peterson on 1/14/16.
//
//

#include <string>
#include "AnimationComponent.h"
#include "AnimTree.h"
#include "../../Entity/EntitySystem.h"
#include "../../../DEFINES.h"

AnimTree::AnimTree( EntityHandle i_entityHandle )
{
    m_entityHandle = i_entityHandle;
    m_activeState = NULL;
}

AnimTree::~AnimTree()
{
    for ( std::map<std::string, AnimTreeState*>::iterator it = m_states.begin(); it != m_states.end(); it++ )
    {
        AnimTreeState* pState = it->second;
        if ( pState )
        {
            delete pState;
        }
    }
    m_states.clear();
}

AnimTree* AnimTree::CreateWithDNA( EntityHandle i_entityHandle, std::string i_fileName )
{
    std::string pPath = "Baked/" + i_fileName;
    std::string fullPath = cocos2d::FileUtils::getInstance()->fullPathForFilename( pPath );
    std::string pFileData = cocos2d::FileUtils::getInstance()->getStringFromFile( fullPath );
    
    rapidjson::Document pDocument;
    pDocument.Parse<rapidjson::kParseStopWhenDoneFlag>( pFileData.c_str() );
    ASSERTS(!pDocument.HasParseError(), "AnimTree DNA parse error!");
    
    AnimTree* pAnimTree = new AnimTree( i_entityHandle );
    pAnimTree->DNADataInit( pDocument );
    
    return pAnimTree;
}

void AnimTree::DNADataInit( const rapidjson::Value& i_dnaObject )
{
    ASSERTS( i_dnaObject.HasMember( "name" ), "AnimTree DNA does not have 'name'" );
    m_name = i_dnaObject["name"].GetString();
    
    ASSERTS( i_dnaObject.HasMember( "states" ), "AnimTree DNA does not have 'states'" );
    for ( int i = 0; i < i_dnaObject["states"].Capacity(); i++ )
    {
        AnimTreeState* pState = new AnimTreeState();
        
        pState->DNADataInit( i_dnaObject["states"][i] );
        m_states.insert( { i_dnaObject["states"][i]["name"].GetString(), pState } );
    }
}

void AnimTree::Start()
{
    EnterState( GetDefaultState() );
}

void AnimTree::Stop()
{
    ExitState( true );
}

void AnimTree::Update( float i_dt )
{
    if ( m_activeState )
    {
        
    }
    else
    {
        EnterState( GetDefaultState() );
    }
}

AnimTreeState* AnimTree::GetDefaultState()
{
    for ( std::map<std::string, AnimTreeState*>::iterator it = m_states.begin(); it != m_states.end(); it++ )
    {
        AnimTreeState* pState = it->second;
        if ( pState )
        {
            if ( pState->IsDefault() )
            {
                return pState;
            }
        }
    }
    return NULL;
}

AnimTreeState* AnimTree::GetState( std::string i_name )
{
    for ( std::map<std::string, AnimTreeState*>::iterator it = m_states.begin(); it != m_states.end(); it++ )
    {
        AnimTreeState* pState = it->second;
        if ( pState )
        {
            if ( std::strcmp( pState->GetName().c_str(), i_name.c_str() ) == 0 )
            {
                return pState;
            }
        }
    }
    return NULL;
}

void AnimTree::EnterState( AnimTreeState* i_state )
{
    if ( m_activeState )
    {
        ExitState( true );
    }
    
    m_activeState = i_state;
    
    AnimationComponent* pComponent = EntitySystem::GetInstance()->GetComponent<AnimationComponent>( m_entityHandle );
    if ( pComponent )
    {
        int loops = 1;
        if ( i_state->IsLooping() )
        {
            loops = 999999999;
        }
        pComponent->StartMotion( i_state->GetMotionName(), loops );
    }
}

void AnimTree::ExitState( bool i_interrupted )
{
    AnimationComponent* pComponent = EntitySystem::GetInstance()->GetComponent<AnimationComponent>( m_entityHandle );
    if ( pComponent )
    {
        pComponent->StopMotion();
    }

    AnimTreeState* pNextState = NULL;
    if ( m_activeState )
    {
        pNextState = GetState( m_activeState->GetExitState() );
        if ( pNextState || m_activeState->ExitsAtEnd() )
        {
            m_activeState = NULL;
        }
    }
    if ( !i_interrupted && pNextState )
    {
        EnterState( pNextState );
    }
}

void AnimTree::SendEvent( std::string i_event )
{
    if ( m_activeState && m_activeState->IgnoresEvent( i_event ) )
    {
        // Our current state has ignored this event
        return;
    }

    AnimTreeState* pNextState = NULL;
    for ( std::map<std::string, AnimTreeState*>::iterator it = m_states.begin(); it != m_states.end(); it++ )
    {
        AnimTreeState* pState = it->second;
        if ( pState )
        {
            if ( pState->RespondsToEvent( i_event ) )
            {
                pNextState = pState;
                break;
            }
        }
    }
    if ( pNextState != NULL )
    {
        EnterState( pNextState );
    }
}