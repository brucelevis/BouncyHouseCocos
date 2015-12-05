//
//  LevelSystem.cpp
//  BouncyHouse
//
//  Created by Derek Peterson on 12/4/15.
//
//

#include "LevelSystem.h"

Level* LevelSystem::m_level;

void LevelSystem::Update( float i_dt )
{
    if ( m_level->GetEnemyCount() < m_level->GetMaxEnemyCount() && m_level->GetEnemySpawnTimer() <= 0.0f )
    {
        m_level->SpawnEnemy();
    }
    m_level->SetEnemySpawnTimer( m_level->GetEnemySpawnTimer() - i_dt );
}