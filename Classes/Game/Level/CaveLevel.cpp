//
//  CaveLevel.cpp
//  BouncyHouse
//
//  Created by Derek Peterson on 1/9/16.
//
//

#include "CaveLevel.h"
#include "../../Engine/Entity/DNASequencer.h"
#include "../../Engine/Entity/EntitySystem.h"
#include "../../Engine/Lighting/LightEffect.h"
#include "../../Engine/Lighting/LightingComponent.h"
#include "../../Engine/Lighting/LightingSystem.h"


void CaveLevel::initLevel()
{
    cocos2d::Size pScreenSize = cocos2d::Director::getInstance()->getOpenGLView()->getDesignResolutionSize();
    
    m_playerSpawner = cocos2d::Vec2( pScreenSize.width * 0.5f, 50.0f );
    m_enemySpawners.push_back( cocos2d::Vec2( 305.0f, 16.0f ) );
    m_enemySpawners.push_back( cocos2d::Vec2( pScreenSize.width - 352.0f, 16.0f ) );
    
    m_maxEnemyCount = 5;
    
    m_player = DNASequencer::CreateEntity( "Baked/Characters/Player/player.dna" );
    PhysicsSystem::GetInstance()->SetPosition( m_player->m_entityHandle, m_playerSpawner );
    
    Entity* pFloor = DNASequencer::CreateEntity( "Baked/Levels/CastleFloor/castlefloor.dna" );
    PhysicsSystem::GetInstance()->SetPosition( pFloor->m_entityHandle, cocos2d::Vec2( pScreenSize.width * 0.5f, 0.0f ) );
    m_staticEntities.insert( std::make_pair( pFloor->m_entityHandle, pFloor ) );
    
    pFloor = DNASequencer::CreateEntity( "Baked/Levels/CastleFloor/castlefloor.dna" );
    PhysicsSystem::GetInstance()->SetPosition( pFloor->m_entityHandle, cocos2d::Vec2( pScreenSize.width * 0.5f, 378.0f ) );
    m_staticEntities.insert( std::make_pair( pFloor->m_entityHandle, pFloor ) );
    
    Entity* pLeftWall = DNASequencer::CreateEntity( "Baked/Characters/Wall/wall.dna" );
    PhysicsSystem::GetInstance()->SetPosition( pLeftWall->m_entityHandle, cocos2d::Vec2( 45.0f, 0.0f ) );
    m_staticEntities.insert( std::make_pair( pLeftWall->m_entityHandle, pLeftWall ) );
    
    Entity* pRightWall = DNASequencer::CreateEntity( "Baked/Characters/Wall/wall.dna" );
    PhysicsSystem::GetInstance()->SetPosition( pRightWall->m_entityHandle, cocos2d::Vec2( pScreenSize.width - 45.0f, 0.0f ) );
    m_staticEntities.insert( std::make_pair( pRightWall->m_entityHandle, pRightWall ) );
    
    
    Entity* pCastle = DNASequencer::CreateEntity( "Baked/Levels/CastleBackground/castlebackground.dna" );
    PhysicsSystem::GetInstance()->SetPosition( pCastle->m_entityHandle, cocos2d::Vec2( pScreenSize.width * 0.5f, 0.0f ) );
    m_staticEntities.insert( std::make_pair( pCastle->m_entityHandle, pCastle ) );
    
    pCastle = DNASequencer::CreateEntity( "Baked/Levels/CastleBackground/castlebackground.dna" );
    PhysicsSystem::GetInstance()->SetPosition( pCastle->m_entityHandle, cocos2d::Vec2( pScreenSize.width * 0.5f, 394.0f ) );
    m_staticEntities.insert( std::make_pair( pCastle->m_entityHandle, pCastle ) );
    
    
    
    Entity* pSky = DNASequencer::CreateEntity( "Baked/Levels/Sky/sky.dna" );
    PhysicsSystem::GetInstance()->SetPosition( pSky->m_entityHandle, cocos2d::Vec2( pScreenSize.width * 0.5f, 0.0f ) );
    m_staticEntities.insert( std::make_pair( pSky->m_entityHandle, pSky ) );
    
    Entity* pMountains = DNASequencer::CreateEntity( "Baked/Levels/Mountains/mountains.dna" );
    PhysicsSystem::GetInstance()->SetPosition( pMountains->m_entityHandle, cocos2d::Vec2( pScreenSize.width * 0.5f, 0.0f ) );
    m_staticEntities.insert( std::make_pair( pMountains->m_entityHandle, pMountains ) );
}

void CaveLevel::update( float i_dt )
{
    Level::update( i_dt );
    
    Entity* pIcicle = EntitySystem::GetInstance()->GetEntity( m_icicleHandle );
    if ( !pIcicle )
    {
        cocos2d::Size pScreenSize = cocos2d::Director::getInstance()->getOpenGLView()->getDesignResolutionSize();
        
        pIcicle = DNASequencer::CreateEntity( "Baked/Characters/Icicle/icicle.dna" );
        float xPos = cocos2d::RandomHelper::random_real( 200.0f, pScreenSize.width - 200.0f );
        PhysicsSystem::GetInstance()->SetPosition( pIcicle->m_entityHandle, cocos2d::Vec2( xPos, pScreenSize.height - 328.0f ) );
        m_staticEntities.insert( std::make_pair( pIcicle->m_entityHandle, pIcicle ) );
        m_icicleHandle = pIcicle->m_entityHandle;
    }
}