//
//  LevelSystem.cpp
//  BouncyHouse
//
//  Created by Derek Peterson on 12/4/15.
//
//

#include "LevelSystem.h"

LevelSystem* LevelSystem::s_instance;

LevelSystem* LevelSystem::GetInstance()
{
    if ( !s_instance )
    {
        s_instance = new LevelSystem();
    }
    return s_instance;
}

void LevelSystem::DestroyInstance()
{
    if ( s_instance )
    {
        delete s_instance;
        s_instance = NULL;
    }
}

void LevelSystem::StartLevel( Level* i_level )
{
    m_level = i_level;
    m_level->initLevel();
}

void LevelSystem::Update( float i_dt )
{
    m_level->update( i_dt );
}
