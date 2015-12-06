//
//  Level.cpp
//  BouncyHouse
//
//  Created by Derek Peterson on 12/4/15.
//
//

#include "../../Engine/Entity/DNASequencer.h"
#include "../../Engine/Entity/EntitySystem.h"
#include "Level.h"
#include "../../Engine/Locomotion/LocomotionComponent.h"
#include "../../Engine/Physics/PhysicsSystem.h"
#include "../../Engine/Render/RenderComponent.h"
#include "../../Engine/Render/RenderSystem.h"

Level::Level()
{
    m_playerSpawner = cocos2d::Vec2( 250.0f, 50.0f );
    m_enemySpawner = cocos2d::Vec2( 1650, 50.0f );
    m_maxEnemyCount = 5;
    m_enemySpawnTimer = 0.0f;
    m_flickerTimer = 0.0f;
    
    m_lightEffect = LightEffect::create();
    m_lightEffect->retain();
    
    m_lightEffect->setLightHalfRadius( 0.8f );
    m_lightEffect->setLightCutoffRadius( 900 );
    m_lightEffect->setBrightness( 2.0f );
    m_lightEffect->setLightPos( cocos2d::Vec3(960, 600, 600) );
    m_lightEffect->setLightColor( cocos2d::Color3B( cocos2d::Color4F( 1.0f, 0.6f, 0.2f, 1.0f ) ) );
    m_lightEffect->setAmbientLightColor( cocos2d::Color3B( cocos2d::Color4F( 0.025f, 0.025f, 0.025f, 1.0f ) ) );
    
    m_player = DNASequencer::CreateEntity( "Baked/Characters/Player/player.dna" );
    PhysicsSystem::SetPosition( m_player->m_entityHandle, m_playerSpawner );
    AddLightEffect( m_player );
    
    
    Entity* pFloor = DNASequencer::CreateEntity( "Baked/Characters/Floor/floor.dna" );
    ASSERTS( pFloor, "Floor is no good!" );
    PhysicsSystem::SetPosition( pFloor->m_entityHandle, cocos2d::Vec2( 960.0f, 15.0f ) );
    m_staticEntities.insert( std::make_pair( pFloor->m_entityHandle, pFloor ) );
    
    Entity* pLeftWall = DNASequencer::CreateEntity( "Baked/Characters/Wall/wall.dna" );
    PhysicsSystem::SetPosition( pLeftWall->m_entityHandle, cocos2d::Vec2( 150.0f, 0.0f ) );
    m_staticEntities.insert( std::make_pair( pLeftWall->m_entityHandle, pLeftWall ) );
    
    Entity* pRightWall = DNASequencer::CreateEntity( "Baked/Characters/Wall/wall.dna" );
    PhysicsSystem::SetPosition( pRightWall->m_entityHandle, cocos2d::Vec2( 1770.0f, 0.0f ) );
    m_staticEntities.insert( std::make_pair( pRightWall->m_entityHandle, pRightWall ) );
    
//    Entity* pSkyBox = DNASequencer::CreateEntity( "Baked/Skybox/skybox.dna" );
//    PhysicsSystem::SetPosition( pSkyBox->m_entityHandle, cocos2d::Vec2( 0.0f, 0.0f ) );
//    m_staticEntities.insert( std::make_pair( pSkyBox->m_entityHandle, pSkyBox ) );
//    
    Entity* pLongboat = DNASequencer::CreateEntity( "Baked/Longboat/longboat.dna" );
    PhysicsSystem::SetPosition( pLongboat->m_entityHandle, cocos2d::Vec2( 1920.0f * 0.5f, 0.0f ) );
    AddLightEffect( pLongboat );
    m_staticEntities.insert( std::make_pair( pLongboat->m_entityHandle, pLongboat ) );
    
    Entity* pLongboatSail = DNASequencer::CreateEntity( "Baked/Longboat/longboat_sail.dna" );
    PhysicsSystem::SetPosition( pLongboatSail->m_entityHandle, cocos2d::Vec2( 1920.0f * 0.5f, 0.0f ) );
    AddLightEffect( pLongboatSail );
    m_staticEntities.insert( std::make_pair( pLongboatSail->m_entityHandle, pLongboatSail ) );
    
    
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
    
    if ( m_lightEffect )
    {
        m_lightEffect->release();
    }
}

void Level::update( float i_dt )
{
    if ( GetEnemyCount() < GetMaxEnemyCount() && GetEnemySpawnTimer() <= 0.0f )
    {
        SpawnEnemy();
    }
    SetEnemySpawnTimer( GetEnemySpawnTimer() - i_dt );
    
    m_flickerTimer -= i_dt;
    if ( m_flickerTimer < 0.0f )
    {
        m_flickerTimer = 0.25f;
        m_flickerTime = m_flickerTimer;
        
        if ( m_lightEffect )
        {
            m_startBrightness = m_targetBrightness;
            m_targetBrightness = cocos2d::RandomHelper::random_real( 1.0f, 3.0f );
        }
    }
    if ( m_lightEffect )
    {
        float pDiff = m_targetBrightness - m_startBrightness;
        float pPercent = ( m_flickerTime - m_flickerTimer ) / m_flickerTime;
        float pBriDiff = pDiff * pPercent;
        float pBrightness = m_startBrightness + pBriDiff;
        m_lightEffect->setBrightness( pBrightness );
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
        pLocomotionComponent->SetRunSpeed( pLocomotionComponent->GetRunSpeed() * cocos2d::RandomHelper::random_real( 0.5f, 1.5f ) );
    }
    AddLightEffect( pEnemy );
    
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

void Level::AddLightEffect( Entity *i_entity )
{
    if ( i_entity )
    {
        RenderComponent* pRenderComponent = EntitySystem::GetComponent<RenderComponent>( i_entity->m_entityHandle );
        if ( pRenderComponent )
        {
            pRenderComponent->SetEffect( m_lightEffect );
        }
    }
}