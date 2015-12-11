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
#include "Level.h"
#include "../../Engine/Lighting/LightingComponent.h"
#include "../../Engine/Lighting/LightingSystem.h"
#include "../../Engine/Locomotion/LocomotionComponent.h"
#include "../../Engine/Physics/PhysicsComponent.h"
#include "../../Engine/Physics/PhysicsSystem.h"
#include "../../Engine/Render/RenderComponent.h"
#include "../../Engine/Render/RenderSystem.h"

#define LIGHT_BRIGHTNESS 3.0f
#define ENEMY_SPAWN_INTERVAL 0.75f

Level::Level()
{
    cocos2d::Size pScreenSize = cocos2d::Director::getInstance()->getOpenGLView()->getDesignResolutionSize();
    
    m_playerSpawner = cocos2d::Vec2( pScreenSize.width * 0.5f, 50.0f );
    m_enemySpawners.push_back( cocos2d::Vec2( 200.0f, 50.0f ) );
    m_enemySpawners.push_back( cocos2d::Vec2( pScreenSize.width - 200.0f, 50.0f ) );
    
    m_maxEnemyCount = 3;
    m_enemySpawnTimer = ENEMY_SPAWN_INTERVAL;
    m_flickerTimer = 0.0f;
    
    
    LightEffect* pLightEffect1 = LightEffect::create();
    pLightEffect1->retain();
    pLightEffect1->setLightPos( cocos2d::Vec3( 200.0f, 100.0f, 50.0f ) );
    pLightEffect1->setLightHalfRadius( 0.5f );
    pLightEffect1->setLightCutoffRadius( 75.0f );
    pLightEffect1->setBrightness( 2.0f );
    pLightEffect1->setLightColor( cocos2d::Color3B( 255.0f, 0.0f, 0.0f ) );
    LightingSystem::AddLightEffect( pLightEffect1 );
    
    LightEffect* pLightEffect = LightEffect::create();
    pLightEffect->retain();
    pLightEffect->setLightPos( cocos2d::Vec3( pScreenSize.width * 0.5f, pScreenSize.height * 2.0f, pScreenSize.height * 2.0f ) );
    pLightEffect->setLightHalfRadius( 1.0f );
    pLightEffect->setLightCutoffRadius( 20000.0f );
    pLightEffect->setBrightness( 2.0f );
    pLightEffect->setLightColor( cocos2d::Color3B( 255.0f, 0.0f, 0.0f ) ); //3.0f, 5.0f, 24.0f ) );
    LightingSystem::AddLightEffect( pLightEffect );

    
    m_player = DNASequencer::CreateEntity( "Baked/Characters/Player/player.dna" );
    PhysicsSystem::SetPosition( m_player->m_entityHandle, m_playerSpawner );
    LightingComponent* pLightingComponent = (LightingComponent*) EntitySystem::AttachComponent( m_player->m_entityHandle, "LightingComponent" );
    if ( pLightingComponent )
    {
        pLightingComponent->Activate();
        pLightingComponent->SetLightEffect( cocos2d::Vec3( 0.0f, 100.0f, 100.0f ), 3.0f, cocos2d::Color3B( 255.0f, 147.0f, 41.0f ), 500.0f, 0.5f );
    }
    
    
    Entity* pFloor = DNASequencer::CreateEntity( "Baked/Characters/Floor/floor.dna" );
    PhysicsSystem::SetPosition( pFloor->m_entityHandle, cocos2d::Vec2( pScreenSize.width * 0.5f, 15.0f ) );
    m_staticEntities.insert( std::make_pair( pFloor->m_entityHandle, pFloor ) );
    
    Entity* pLeftWall = DNASequencer::CreateEntity( "Baked/Characters/Wall/wall.dna" );
    PhysicsSystem::SetPosition( pLeftWall->m_entityHandle, cocos2d::Vec2( 45.0f, 0.0f ) );
    m_staticEntities.insert( std::make_pair( pLeftWall->m_entityHandle, pLeftWall ) );
    
    Entity* pRightWall = DNASequencer::CreateEntity( "Baked/Characters/Wall/wall.dna" );
    PhysicsSystem::SetPosition( pRightWall->m_entityHandle, cocos2d::Vec2( pScreenSize.width - 45.0f, 0.0f ) );
    m_staticEntities.insert( std::make_pair( pRightWall->m_entityHandle, pRightWall ) );

    Entity* pLongboat = DNASequencer::CreateEntity( "Baked/Longboat/longboat.dna" );
    PhysicsSystem::SetPosition( pLongboat->m_entityHandle, cocos2d::Vec2( pScreenSize.width * 0.5f, 0.0f ) );
    m_staticEntities.insert( std::make_pair( pLongboat->m_entityHandle, pLongboat ) );
    
    Entity* pLongboatSail = DNASequencer::CreateEntity( "Baked/Longboat/longboat_sail.dna" );
    PhysicsSystem::SetPosition( pLongboatSail->m_entityHandle, cocos2d::Vec2( pScreenSize.width * 0.5f, 70.0f ) );
    m_staticEntities.insert( std::make_pair( pLongboatSail->m_entityHandle, pLongboatSail ) );
    
    Entity* pSkyBox = DNASequencer::CreateEntity( "Baked/Skybox/skybox.dna" );
    PhysicsSystem::SetPosition( pSkyBox->m_entityHandle, cocos2d::Vec2( 0.0f, 0.0f ) );
    m_staticEntities.insert( std::make_pair( pSkyBox->m_entityHandle, pSkyBox ) );
    
    
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
        
        m_startBrightness = m_targetBrightness;
        m_targetBrightness = cocos2d::RandomHelper::random_real( LIGHT_BRIGHTNESS * 0.25f, LIGHT_BRIGHTNESS );
    }
    float pDiff = m_targetBrightness - m_startBrightness;
    float pPercent = ( m_flickerTime - m_flickerTimer ) / m_flickerTime;
    float pBriDiff = pDiff * pPercent;
    float pBrightness = m_startBrightness + pBriDiff;
//    m_lightEffect->setBrightness( pBrightness );
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
