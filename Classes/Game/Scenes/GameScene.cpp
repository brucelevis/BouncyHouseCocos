//
//  GameScene.cpp
//  BouncyHouse
//
//  Created by Derek Peterson on 11/30/15.
//
//

#include "../GameSpecificInit.h"
#include "../../Engine/AI/AISystem.h"
#include "../../Engine/Animation/AnimationSystem.h"
#include "../../Engine/Entity/ComponentSystem.h"
#include "../../Engine/Entity/DNASequencer.h"
#include "../../Engine/Entity/EntitySystem.h"
#include "../../Engine/Event/EventManager.h"
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
    GameSpecificInit::Init();
    
    PhysicsSystem::GetInstance()->SetPhysicsWorld( this->getPhysicsWorld() );
    PhysicsSystem::GetInstance()->GetPhysicsWorld()->setGravity( cocos2d::Vec2( 0.0f, GRAVITY ) );
    PhysicsSystem::GetInstance()->GetPhysicsWorld()->setAutoStep( false );
    
    RenderSystem::GetInstance()->SetScene( this );
    RenderSystem::GetInstance()->GetScene()->scheduleUpdate();
    
    ComponentSystem::GetInstance()->DNADataInit();
    HealthSystem::GetInstance()->DNADataInit();
    LocomotionSystem::GetInstance()->DNADataInit();
    PhysicsSystem::GetInstance()->DNADataInit();
    
    LevelSystem::GetInstance()->StartLevel( new CaveLevel() );

    auto eventListener = cocos2d::EventListenerKeyboard::create();
    eventListener->onKeyPressed = [](cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event){
        cocos2d::Vec2 loc = event->getCurrentTarget()->getPosition();
        switch( keyCode ){
            case cocos2d::EventKeyboard::KeyCode::KEY_SPACE:
            {
                EventManager::GetInstance()->SendEvent("AvatarAction_Jump", &LevelSystem::GetInstance()->GetLevel()->GetPlayer()->m_entityHandle );
                break;
            }
            case cocos2d::EventKeyboard::KeyCode::KEY_C:
            {
                PhysicsSystem::GetInstance()->SetDebug( !PhysicsSystem::GetInstance()->GetDebug() );
                if ( PhysicsSystem::GetInstance()->GetDebug() )
                {
                    PhysicsSystem::GetInstance()->GetPhysicsWorld()->setDebugDrawMask(cocos2d::PhysicsWorld::DEBUGDRAW_ALL);
                }
                else
                {
                    PhysicsSystem::GetInstance()->GetPhysicsWorld()->setDebugDrawMask(cocos2d::PhysicsWorld::DEBUGDRAW_NONE);
                }
                break;
            }
            case cocos2d::EventKeyboard::KeyCode::KEY_L:
            {
                LocomotionSystem::GetInstance()->SetDebug( !LocomotionSystem::GetInstance()->GetDebug() );
                break;
            }
            case cocos2d::EventKeyboard::KeyCode::KEY_A:
            {
                AnimationSystem::GetInstance()->SetDebug( !AnimationSystem::GetInstance()->GetDebug() );
                break;
            }
            case cocos2d::EventKeyboard::KeyCode::KEY_I:
            {
                AISystem::GetInstance()->SetDebug( !AISystem::GetInstance()->GetDebug() );
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
                break;
            }
            case cocos2d::EventKeyboard::KeyCode::KEY_R:
            {
                RenderSystem::GetInstance()->SetDebug( !RenderSystem::GetInstance()->GetDebug() );
                break;
            }
            default:
            {
                break;
            }
        }
    };
    this->_eventDispatcher->addEventListenerWithSceneGraphPriority(eventListener, this);
    
    auto touchListener = cocos2d::EventListenerTouchOneByOne::create();
    touchListener->onTouchBegan = touchListener->onTouchBegan = [](cocos2d::Touch* touch, cocos2d::Event* event){
        EventManager::GetInstance()->SendEvent("AvatarAction_Jump", &LevelSystem::GetInstance()->GetLevel()->GetPlayer()->m_entityHandle );
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
    LevelSystem::GetInstance()->Update( i_dt );
    
    GroundDetectSystem::GetInstance()->Update( i_dt );
    AnimationSystem::GetInstance()->Update( i_dt );
    AISystem::GetInstance()->Update( i_dt );
    LocomotionSystem::GetInstance()->Update( i_dt );
    PhysicsSystem::GetInstance()->Update( i_dt );
    LightingSystem::GetInstance()->Update( i_dt );
    HealthSystem::GetInstance()->Update( i_dt );
    EntitySystem::GetInstance()->Update( i_dt );
    RenderSystem::GetInstance()->Update( i_dt );
}

bool GameScene::OnContactBegin( cocos2d::PhysicsContact& i_contact )
{
    return PhysicsSystem::GetInstance()->OnContactBegin( i_contact );
}

void GameScene::OnContactPostSolve( cocos2d::PhysicsContact& i_contact )
{
    PhysicsSystem::GetInstance()->OnContactPostSolve( i_contact );
}
