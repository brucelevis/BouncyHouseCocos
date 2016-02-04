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
    float pHorizontalCenter = pScreenSize.width * 0.5f;
    
    m_playerSpawner = cocos2d::Vec2( pScreenSize.width * 0.5f, 50.0f );
    m_enemySpawners.push_back( cocos2d::Vec2( 349.0f, 16.0f ) );
    m_enemySpawners.push_back( cocos2d::Vec2( pScreenSize.width - 301.0f, 16.0f ) );
    
    m_maxEnemyCount = 5;
    
    m_player = DNASequencer::CreateEntity( "Baked/Characters/Player/player.dna" );
    PhysicsSystem::GetInstance()->SetPosition( m_player->m_entityHandle, m_playerSpawner );
    
    Entity* pSky = DNASequencer::CreateEntity( "Baked/Levels/Sky/sky.dna" );
    PhysicsSystem::GetInstance()->SetPosition( pSky->m_entityHandle, cocos2d::Vec2( pHorizontalCenter, 0.0f ) );
    m_staticEntities.insert( std::make_pair( pSky->m_entityHandle, pSky ) );
    
    Entity* pMountains = DNASequencer::CreateEntity( "Baked/Levels/Mountains/mountains.dna" );
    PhysicsSystem::GetInstance()->SetPosition( pMountains->m_entityHandle, cocos2d::Vec2( pHorizontalCenter, 0.0f ) );
    m_staticEntities.insert( std::make_pair( pMountains->m_entityHandle, pMountains ) );

    
    for ( int j = 0; j < 2; j++ )
    {
        Entity* pFloor = DNASequencer::CreateEntity( "Baked/Levels/CastleFloor/castlefloor.dna" );
        PhysicsSystem::GetInstance()->SetPosition( pFloor->m_entityHandle, cocos2d::Vec2( pHorizontalCenter, 590.0f * j ) );
        m_staticEntities.insert( std::make_pair( pFloor->m_entityHandle, pFloor ) );
        
        Entity* pCastle = DNASequencer::CreateEntity( "Baked/Levels/CastleBackground/castlebackground.dna" );
        PhysicsSystem::GetInstance()->SetPosition( pCastle->m_entityHandle, cocos2d::Vec2( pHorizontalCenter, 590.0f * j ) );
        m_staticEntities.insert( std::make_pair( pCastle->m_entityHandle, pCastle ) );
        
        for ( int i = 0; i < 6; i++ )
        {
            Entity* pWall = DNASequencer::CreateEntity( "Baked/Levels/CastleWall/castlewall.dna" );
            PhysicsSystem::GetInstance()->SetPosition( pWall->m_entityHandle, cocos2d::Vec2( 115.0f, 112.0f * i + 590.0f * j - 4.0f ) );
            m_staticEntities.insert( std::make_pair( pWall->m_entityHandle, pWall ) );
            
            pWall = DNASequencer::CreateEntity( "Baked/Levels/CastleWall/castlewall.dna" );
            PhysicsSystem::GetInstance()->SetPosition( pWall->m_entityHandle, cocos2d::Vec2( 1920.0f - 115.0f, 112.0f * i + 590.0f * j - 4.0f ) );
            m_staticEntities.insert( std::make_pair( pWall->m_entityHandle, pWall ) );
        }
    }
}

void CaveLevel::update( float i_dt )
{
    Level::update( i_dt );
    
//    Entity* pIcicle = EntitySystem::GetInstance()->GetEntity( m_icicleHandle );
//    if ( !pIcicle )
//    {
//        cocos2d::Size pScreenSize = cocos2d::Director::getInstance()->getOpenGLView()->getDesignResolutionSize();
//        
//        pIcicle = DNASequencer::CreateEntity( "Baked/Characters/Icicle/icicle.dna" );
//        float xPos = cocos2d::RandomHelper::random_real( 200.0f, pScreenSize.width - 200.0f );
//        PhysicsSystem::GetInstance()->SetPosition( pIcicle->m_entityHandle, cocos2d::Vec2( xPos, pScreenSize.height - 328.0f ) );
//        m_staticEntities.insert( std::make_pair( pIcicle->m_entityHandle, pIcicle ) );
//        m_icicleHandle = pIcicle->m_entityHandle;
//    }
}