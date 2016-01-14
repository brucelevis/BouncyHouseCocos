//
//  ShipLevel.cpp
//  BouncyHouse
//
//  Created by Derek Peterson on 1/9/16.
//
//

#include "ShipLevel.h"
#include "../../Engine/Entity/DNASequencer.h"
#include "../../Engine/Entity/EntitySystem.h"
#include "../../Engine/Lighting/LightEffect.h"
#include "../../Engine/Lighting/LightingComponent.h"
#include "../../Engine/Lighting/LightingSystem.h"


void ShipLevel::initLevel()
{
    cocos2d::Size pScreenSize = cocos2d::Director::getInstance()->getOpenGLView()->getDesignResolutionSize();
    
    m_playerSpawner = cocos2d::Vec2( pScreenSize.width * 0.5f, 50.0f );
    m_enemySpawners.push_back( cocos2d::Vec2( 200.0f, 50.0f ) );
    m_enemySpawners.push_back( cocos2d::Vec2( pScreenSize.width - 200.0f, 50.0f ) );
    
    m_maxEnemyCount = 3;
    
    
    LightEffect* pLightEffect1 = LightEffect::create();
    pLightEffect1->retain();
    pLightEffect1->setLightPos( cocos2d::Vec3( 200.0f, 100.0f, 50.0f ) );
    pLightEffect1->setLightHalfRadius( 0.5f );
    pLightEffect1->setLightCutoffRadius( 75.0f );
    pLightEffect1->setBrightness( 2.0f );
    pLightEffect1->setLightColor( cocos2d::Color3B( 255.0f, 0.0f, 0.0f ) );
    LightingSystem::GetInstance()->AddLightEffect( pLightEffect1 );
    
    LightEffect* pLightEffect = LightEffect::create();
    pLightEffect->retain();
    pLightEffect->setLightPos( cocos2d::Vec3( pScreenSize.width * 0.5f, pScreenSize.height * 2.0f, 200.0f ) );
    pLightEffect->setLightHalfRadius( 1.0f );
    pLightEffect->setLightCutoffRadius( 9000.0 );
    pLightEffect->setBrightness( 2.0f );
    pLightEffect->setLightColor( cocos2d::Color3B( 255.0f, 255.0f, 255.0f ) ); //3.0f, 5.0f, 24.0f ) );
    LightingSystem::GetInstance()->AddLightEffect( pLightEffect );
    
    
    m_player = DNASequencer::CreateEntity( "Baked/Characters/Player/player.dna" );
    PhysicsSystem::GetInstance()->SetPosition( m_player->m_entityHandle, m_playerSpawner );
    LightingComponent* pLightingComponent = (LightingComponent*) EntitySystem::GetInstance()->AttachComponent( m_player->m_entityHandle, "LightingComponent" );
    if ( pLightingComponent )
    {
        pLightingComponent->Activate();
        pLightingComponent->SetLightEffect( cocos2d::Vec3( 0.0f, 100.0f, 100.0f ), 3.0f, cocos2d::Color3B( 255.0f, 147.0f, 41.0f ), 500.0f, 0.5f );
    }
    
    
    Entity* pFloor = DNASequencer::CreateEntity( "Baked/Characters/Floor/floor.dna" );
    PhysicsSystem::GetInstance()->SetPosition( pFloor->m_entityHandle, cocos2d::Vec2( pScreenSize.width * 0.5f, 15.0f ) );
    m_staticEntities.insert( std::make_pair( pFloor->m_entityHandle, pFloor ) );
    
    Entity* pLeftWall = DNASequencer::CreateEntity( "Baked/Characters/Wall/wall.dna" );
    PhysicsSystem::GetInstance()->SetPosition( pLeftWall->m_entityHandle, cocos2d::Vec2( 45.0f, 0.0f ) );
    m_staticEntities.insert( std::make_pair( pLeftWall->m_entityHandle, pLeftWall ) );
    
    Entity* pRightWall = DNASequencer::CreateEntity( "Baked/Characters/Wall/wall.dna" );
    PhysicsSystem::GetInstance()->SetPosition( pRightWall->m_entityHandle, cocos2d::Vec2( pScreenSize.width - 45.0f, 0.0f ) );
    m_staticEntities.insert( std::make_pair( pRightWall->m_entityHandle, pRightWall ) );
    
    Entity* pLongboat = DNASequencer::CreateEntity( "Baked/Longboat/longboat.dna" );
    PhysicsSystem::GetInstance()->SetPosition( pLongboat->m_entityHandle, cocos2d::Vec2( pScreenSize.width * 0.5f, 0.0f ) );
    m_staticEntities.insert( std::make_pair( pLongboat->m_entityHandle, pLongboat ) );
    
    Entity* pLongboatSail = DNASequencer::CreateEntity( "Baked/Longboat/longboat_sail.dna" );
    PhysicsSystem::GetInstance()->SetPosition( pLongboatSail->m_entityHandle, cocos2d::Vec2( pScreenSize.width * 0.5f, 70.0f ) );
    m_staticEntities.insert( std::make_pair( pLongboatSail->m_entityHandle, pLongboatSail ) );
    
    Entity* pSkyBox = DNASequencer::CreateEntity( "Baked/Skybox/skybox.dna" );
    PhysicsSystem::GetInstance()->SetPosition( pSkyBox->m_entityHandle, cocos2d::Vec2( 0.0f, 0.0f ) );
    m_staticEntities.insert( std::make_pair( pSkyBox->m_entityHandle, pSkyBox ) );
}