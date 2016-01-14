//
//  Level.cpp
//  BouncyHouse
//
//  Created by Derek Peterson on 12/4/15.
//
//
#include "cocos2d.h"

#include "../../Engine/Entity/DNASequencer.h"
#include "../../Engine/Entity/EntitySystem.h"
#include "../../Engine/Event/EventManager.h"
#include "Level.h"
#include "../../Engine/Locomotion/LocomotionComponent.h"
#include "../../Engine/Physics/PhysicsComponent.h"
#include "../../Engine/Physics/PhysicsSystem.h"
#include "../../Engine/Render/RenderComponent.h"
#include "../../Engine/Render/RenderSystem.h" 

#define ENEMY_SPAWN_INTERVAL 0.75f

Level::Level()
{
    EventManager::GetInstance()->RegisterForEvent( "RemovingEntity", CC_CALLBACK_1( Level::OnRemovingEntityEvent, this ), this );
}

void Level::initLevel() {

}

Level::~Level()
{
    EventManager::GetInstance()->UnregisterForEvent( "RemovingEntity", this );
    for ( std::map<EntityHandle, Entity*>::iterator it = m_enemies.begin(); it != m_enemies.end(); it++ )
    {
        delete it->second;
    }
    for ( std::map<EntityHandle, Entity*>::iterator it = m_staticEntities.begin(); it != m_staticEntities.end(); it++ )
    {
        delete it->second;
    }
}

void Level::update( float i_dt )
{
    if ( GetEnemyCount() < GetMaxEnemyCount() && GetEnemySpawnTimer() <= 0.0f )
    {
        SpawnEnemy();
    }
    SetEnemySpawnTimer( GetEnemySpawnTimer() - i_dt );
}

void Level::SpawnEnemy()
{
    m_enemySpawnTimer = ENEMY_SPAWN_INTERVAL;
    Entity* pEnemy = DNASequencer::CreateEntity( "Baked/Characters/Enemy/enemy.dna" );
    PhysicsSystem::SetPosition( pEnemy->m_entityHandle, m_enemySpawners[ cocos2d::RandomHelper::random_int( 0, (int)m_enemySpawners.size() - 1 ) ] );
    LocomotionComponent* pLocomotionComponent = EntitySystem::GetComponent<LocomotionComponent>( pEnemy->m_entityHandle );
    if ( pLocomotionComponent )
    {
        pLocomotionComponent->SetRunSpeed( pLocomotionComponent->GetRunSpeed() * cocos2d::RandomHelper::random_real( 0.5f, 1.5f ) );
    }
    
    m_enemies.insert( std::make_pair( pEnemy->m_entityHandle, pEnemy ) );
}

void Level::OnRemovingEntityEvent( cocos2d::EventCustom* i_event )
{
    EntityHandle pEntityHandle = *((int*)(i_event->getUserData()));
    if ( m_enemies.count( pEntityHandle ) > 0 )
    {
        m_enemies.erase( pEntityHandle );
        m_enemySpawnTimer = ENEMY_SPAWN_INTERVAL;
    }
    if ( m_staticEntities.count( pEntityHandle ) > 0 )
    {
        m_staticEntities.erase( pEntityHandle );
    }
}
