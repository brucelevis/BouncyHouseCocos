//
//  Level.cpp
//  BouncyHouse
//
//  Created by Derek Peterson on 12/4/15.
//
//

#include "DNASequencer.h"
#include "EntitySystem.h"
#include "Level.h"
#include "LocomotionComponent.h"
#include "PhysicsSystem.h"
#include "RenderSystem.h"

Level::Level()
{
    m_playerSpawner = cocos2d::Vec2( 100.0f, 50.0f );
    m_enemySpawner = cocos2d::Vec2( 1820, 50.0f );
    m_maxEnemyCount = 5;
    m_enemySpawnTimer = 0.0f;
    
    m_player = DNASequencer::CreateEntity( "Baked/Characters/Player/player.dna" );
    PhysicsSystem::SetPosition( m_player->m_entityHandle, m_playerSpawner );
    
    
    Entity* pFloor = DNASequencer::CreateEntity( "Baked/Characters/Floor/floor.dna" );
    PhysicsSystem::SetPosition( pFloor->m_entityHandle, cocos2d::Vec2( 960.0f, 0.0f ) );
    m_staticEntities.insert( std::make_pair( pFloor->m_entityHandle, pFloor ) );
    Entity* pLeftWall = DNASequencer::CreateEntity( "Baked/Characters/Wall/wall.dna" );
    PhysicsSystem::SetPosition( pLeftWall->m_entityHandle, cocos2d::Vec2( 0.0f, 0.0f ) );
    m_staticEntities.insert( std::make_pair( pLeftWall->m_entityHandle, pLeftWall ) );
    Entity* pRightWall = DNASequencer::CreateEntity( "Baked/Characters/Wall/wall.dna" );
    PhysicsSystem::SetPosition( pRightWall->m_entityHandle, cocos2d::Vec2( 1920.0f, 0.0f ) );
    m_staticEntities.insert( std::make_pair( pRightWall->m_entityHandle, pRightWall ) );
    
    
    cocos2d::EventListenerCustom* pRemovingEntityListener = cocos2d::EventListenerCustom::create( "RemovingEntity", CC_CALLBACK_1( Level::OnRemovingEntityEvent, this ) );
    RenderSystem::m_activeScene->GetEventDispatcher()->addEventListenerWithFixedPriority( pRemovingEntityListener, 1 );
}

Level::~Level()
{
    for ( std::map<EntityHandle, Entity*>::iterator it = m_enemies.begin(); it != m_enemies.end(); it++ )
    {
        delete it->second;
    }
    for ( std::map<EntityHandle, Entity*>::iterator it = m_staticEntities.begin(); it != m_staticEntities.end(); it++ )
    {
        delete it->second;
    }
}

void Level::SpawnEnemy()
{
    m_enemySpawnTimer = 0.25f;
    Entity* pEnemy = DNASequencer::CreateEntity( "Baked/Characters/Enemy/enemy.dna" );
    PhysicsSystem::SetPosition( pEnemy->m_entityHandle, m_enemySpawner );
    LocomotionComponent* pLocomotionComponent = EntitySystem::GetComponent<LocomotionComponent>( pEnemy->m_entityHandle );
    if ( pLocomotionComponent )
    {
        pLocomotionComponent->SetRunSpeed( pLocomotionComponent->GetRunSpeed() * cocos2d::RandomHelper::random_real( 0.75f, 1.25f ) );
    }
    
    m_enemies.insert( std::make_pair( pEnemy->m_entityHandle, pEnemy ) );
}

void Level::OnRemovingEntityEvent( cocos2d::EventCustom* i_event )
{
    EntityHandle pEntityHandle = *((int*)(i_event->getUserData()));
    if ( m_enemies.count( pEntityHandle ) > 0 )
    {
        m_enemies.erase( pEntityHandle );
    }
    if ( m_staticEntities.count( pEntityHandle ) > 0 )
    {
        m_staticEntities.erase( pEntityHandle );
    }
}