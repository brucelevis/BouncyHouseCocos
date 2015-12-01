//
//  GameScene.cpp
//  BouncyHouse
//
//  Created by Derek Peterson on 11/30/15.
//
//

#include "ComponentSystem.h"
#include "DNASequencer.h"
#include "EntitySystem.h"
#include "GameScene.h"
#include "PhysicsComponent.h"
#include "PhysicsSystem.h"
#include "RenderComponent.h"
#include "RenderSystem.h"

USING_NS_CC;

// on "init" you need to initialize your instance
bool GameScene::Start()
{
    this->getPhysicsWorld()->setGravity( Vec2( 0.0f, -1500.0f ) );
    this->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
    
    RenderSystem::m_activeScene = this;
    RenderSystem::m_activeScene->scheduleUpdate();
    ComponentSystem::Init();
    
    Entity* pPlayer = DNASequencer::CreateEntity( "Baked/Characters/Player/player.dna" );
    PhysicsSystem::SetPosition( pPlayer->m_entityHandle, cocos2d::Vec2( 100, 500.0f ) );
    Entity* pFloor = DNASequencer::CreateEntity( "Baked/Characters/Floor/floor.dna" );
    PhysicsSystem::SetPosition( pFloor->m_entityHandle, cocos2d::Vec2( 960.0f, 0.0f ) );
    
    Entity* pLeftWall = DNASequencer::CreateEntity( "Baked/Characters/Wall/wall.dna" );
    PhysicsSystem::SetPosition( pLeftWall->m_entityHandle, cocos2d::Vec2( 0.0f, 0.0f ) );
    Entity* pRightWall = DNASequencer::CreateEntity( "Baked/Characters/Wall/wall.dna" );
    PhysicsSystem::SetPosition( pRightWall->m_entityHandle, cocos2d::Vec2( 1920.0f, 0.0f ) );
    
    return true;
}


void GameScene::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

void GameScene::update( float i_dt )
{
    PhysicsSystem::Update( i_dt );
    EntitySystem::Update( i_dt );
    RenderSystem::Update( i_dt );
}
