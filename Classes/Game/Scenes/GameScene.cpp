//
//  GameScene.cpp
//  BouncyHouse
//
//  Created by Derek Peterson on 11/30/15.
//
//

#include "../../Engine/Animation/AnimationSystem.h"
#include "../../Engine/Entity/ComponentSystem.h"
#include "../../Engine/Entity/DNASequencer.h"
#include "../../Engine/Entity/EntitySystem.h"
#include "GameScene.h"
#include "../../Engine/GroundDetect/GroundDetectSystem.h"
#include "../../Engine/Health/HealthSystem.h"
#include "../Level/LevelSystem.h"
#include "../Level/CaveLevel.h"
#include "../../Engine/Lighting/LightingSystem.h"
#include "../../Engine/Locomotion/LocomotionComponent.h"
#include "../../Engine/Locomotion/LocomotionSystem.h"
#include "../../Engine/Physics/PhysicsSystem.h"
#include "../../Engine/Render/RenderSystem.h"

// on "init" you need to initialize your instance
bool GameScene::Start()
{
    this->getPhysicsWorld()->setGravity( cocos2d::Vec2( 0.0f, GRAVITY ) );
    this->getPhysicsWorld()->setAutoStep( false );
    
    RenderSystem::GetInstance()->SetScene( this );
    RenderSystem::GetInstance()->GetScene()->scheduleUpdate();
    
    ComponentSystem::DNADataInit();
    HealthSystem::DNADataInit();
    LocomotionSystem::DNADataInit();
    PhysicsSystem::DNADataInit();
    
    LevelSystem::StartLevel( new CaveLevel() );

    auto eventListener = cocos2d::EventListenerKeyboard::create();
    eventListener->onKeyPressed = [](cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event){
        cocos2d::Vec2 loc = event->getCurrentTarget()->getPosition();
        switch( keyCode ){
            case cocos2d::EventKeyboard::KeyCode::KEY_SPACE:
            {
                LocomotionComponent* pLocomotionComponent = EntitySystem::GetComponent<LocomotionComponent>( LevelSystem::GetLevel()->GetPlayer()->m_entityHandle );
                if ( pLocomotionComponent && pLocomotionComponent->m_locomotionMode )
                {
                    pLocomotionComponent->m_locomotionMode->Jump();
                }
                break;
            }
            case cocos2d::EventKeyboard::KeyCode::KEY_C:
            {
                PhysicsSystem::m_debug = !PhysicsSystem::m_debug;
                if ( PhysicsSystem::m_debug )
                {
                    RenderSystem::GetInstance()->GetScene()->getPhysicsWorld()->setDebugDrawMask(cocos2d::PhysicsWorld::DEBUGDRAW_ALL);
                }
                else
                {
                    RenderSystem::GetInstance()->GetScene()->getPhysicsWorld()->setDebugDrawMask(cocos2d::PhysicsWorld::DEBUGDRAW_NONE);
                }
                break;
            }
            case cocos2d::EventKeyboard::KeyCode::KEY_L:
            {
                LocomotionSystem::m_debug = !LocomotionSystem::m_debug;
                break;
            }
            case cocos2d::EventKeyboard::KeyCode::KEY_A:
            {
                AnimationSystem::m_debug = !AnimationSystem::m_debug;
                break;
            }
            case cocos2d::EventKeyboard::KeyCode::KEY_S:
            {
                if ( cocos2d::Director::getInstance()->getScheduler()->getTimeScale() != 0.1f )
                {
                    cocos2d::Director::getInstance()->getScheduler()->setTimeScale( 0.1f);
                }
                else
                {
                    cocos2d::Director::getInstance()->getScheduler()->setTimeScale( 1.0f);
                }
                break;
            }
            case cocos2d::EventKeyboard::KeyCode::KEY_P:
            {
                if ( cocos2d::Director::getInstance()->getScheduler()->getTimeScale() > 0.0f )
                {
                    cocos2d::Director::getInstance()->getScheduler()->setTimeScale( 0.0f );
                }
                else
                {
                    cocos2d::Director::getInstance()->getScheduler()->setTimeScale( 1.0f );
                }
            }
        }
    };
    this->_eventDispatcher->addEventListenerWithSceneGraphPriority(eventListener, this);
    
    auto touchListener = cocos2d::EventListenerTouchOneByOne::create();
    touchListener->onTouchBegan = touchListener->onTouchBegan = [](cocos2d::Touch* touch, cocos2d::Event* event){
        LocomotionComponent* pLocomotionComponent = EntitySystem::GetComponent<LocomotionComponent>( LevelSystem::GetLevel()->GetPlayer()->m_entityHandle );
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
    cocos2d::Director::getInstance()->end();
    
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
    LightingSystem::Update( i_dt );
    HealthSystem::Update( i_dt );
    EntitySystem::Update( i_dt );
    RenderSystem::GetInstance()->Update( i_dt );
}

bool GameScene::OnContactBegin( cocos2d::PhysicsContact& i_contact )
{
    return PhysicsSystem::OnContactBegin( i_contact );
}

void GameScene::OnContactPostSolve( cocos2d::PhysicsContact& i_contact )
{
    PhysicsSystem::OnContactPostSolve( i_contact );
}
