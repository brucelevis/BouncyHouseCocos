//
//  LevelSystem.cpp
//  BouncyHouse
//
//  Created by Derek Peterson on 12/4/15.
//
//

#include "LevelSystem.h"

Level* LevelSystem::m_level;

void LevelSystem::StartLevel( Level* i_level )
{
    m_level = i_level;
    m_level->initLevel();
}

void LevelSystem::Update( float i_dt )
{
    m_level->update( i_dt );
}
