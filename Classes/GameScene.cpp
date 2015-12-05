//
//  GameScene.cpp
//  BouncyHouse
//
//  Created by Derek Peterson on 11/30/15.
//
//

#include "AnimationSystem.h"
#include "ComponentSystem.h"
#include "DNASequencer.h"
#include "EntitySystem.h"
#include "GameScene.h"
#include "GroundDetectSystem.h"
#include "Level.h"
#include "LevelSystem.h"
#include "LocomotionComponent.h"
#include "LocomotionSystem.h"
#include "PhysicsSystem.h"
#include "RenderSystem.h"

USING_NS_CC;

// on "init" you need to initialize your instance
bool GameScene::Start()
{
    this->getPhysicsWorld()->setGravity( Vec2( 0.0f, -1500.0f ) );
    this->getPhysicsWorld()->setAutoStep( false );
    
    RenderSystem::m_activeScene = this;
    RenderSystem::m_activeScene->scheduleUpdate();
    ComponentSystem::Init();
    LocomotionSystem::Init();
    PhysicsSystem::Init();
    
    LevelSystem::m_level = new Level();

    auto eventListener = EventListenerKeyboard::create();
    eventListener->onKeyPressed = [](EventKeyboard::KeyCode keyCode, Event* event){
        Vec2 loc = event->getCurrentTarget()->getPosition();
        switch(keyCode){
            case EventKeyboard::KeyCode::KEY_SPACE:
            {
                LocomotionComponent* pLocomotionComponent = EntitySystem::GetComponent<LocomotionComponent>( LevelSystem::m_level->GetPlayer()->m_entityHandle );
                if ( pLocomotionComponent && pLocomotionComponent->m_locomotionMode )
                {
                    pLocomotionComponent->m_locomotionMode->Jump();
                }
                break;
            }
            case EventKeyboard::KeyCode::KEY_P:
            {
                PhysicsSystem::m_debug = !PhysicsSystem::m_debug;
                if ( PhysicsSystem::m_debug )
                {
                    RenderSystem::m_activeScene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
                }
                else
                {
                    RenderSystem::m_activeScene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_NONE);
                }
                break;
            }
            case EventKeyboard::KeyCode::KEY_L:
            {
                LocomotionSystem::m_debug = !LocomotionSystem::m_debug;
                break;
            }
            case EventKeyboard::KeyCode::KEY_A:
            {
                AnimationSystem::m_debug = !AnimationSystem::m_debug;
                break;
            }
            case EventKeyboard::KeyCode::KEY_S:
            {
                RenderSystem::m_activeScene->m_slowMotion = !RenderSystem::m_activeScene->m_slowMotion;
                if ( RenderSystem::m_activeScene->m_slowMotion )
                {
                    Director::getInstance()->getScheduler()->setTimeScale( 0.25f);
                }
                else
                {
                    Director::getInstance()->getScheduler()->setTimeScale( 1.0f);
                }
                break;
            }
        }
    };
    this->_eventDispatcher->addEventListenerWithSceneGraphPriority(eventListener, this);
    
    auto touchListener = EventListenerTouchOneByOne::create();
    touchListener->onTouchBegan = touchListener->onTouchBegan = [](Touch* touch, Event* event){
        LocomotionComponent* pLocomotionComponent = EntitySystem::GetComponent<LocomotionComponent>( LevelSystem::m_level->GetPlayer()->m_entityHandle );
        if ( pLocomotionComponent && pLocomotionComponent->m_locomotionMode )
        {
            pLocomotionComponent->m_locomotionMode->Jump();
        }
        return true;
    };
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener, this);
    
    auto contactBeginListener = cocos2d::EventListenerPhysicsContact::create();
    contactBeginListener->onContactBegin = CC_CALLBACK_1( GameScene::OnContactBegin, this );
    this->_eventDispatcher->addEventListenerWithSceneGraphPriority( contactBeginListener, this );
    
    auto contactPostSolveListener = cocos2d::EventListenerPhysicsContact::create();
    contactPostSolveListener->onContactPostSolve = CC_CALLBACK_1( GameScene::OnContactPostSolve, this );
    this->_eventDispatcher->addEventListenerWithSceneGraphPriority( contactPostSolveListener, this );
    
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
    LevelSystem::Update( i_dt );
    
    GroundDetectSystem::Update( i_dt );
    AnimationSystem::Update( i_dt );
    LocomotionSystem::Update( i_dt );
    PhysicsSystem::Update( i_dt );
    EntitySystem::Update( i_dt );
    RenderSystem::Update( i_dt );
}

bool GameScene::OnContactBegin( cocos2d::PhysicsContact& i_contact )
{
    return PhysicsSystem::OnContactBegin( i_contact );
}

bool GameScene::OnContactPostSolve( cocos2d::PhysicsContact& i_contact )
{
    return PhysicsSystem::OnContactPostSolve( i_contact );
}