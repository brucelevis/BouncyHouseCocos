#include "HelloWorldScene.h"
#include "ComponentSystem.h"
#include "DNASequencer.h"
#include "EntitySystem.h"
#include "PhysicsComponent.h"
#include "PhysicsSystem.h"
#include "RenderComponent.h"
#include "RenderSystem.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    ComponentSystem::Init();
    
    // 'scene' is an autorelease object
    auto scene = Scene::createWithPhysics();
    scene->getPhysicsWorld()->setGravity( Vec2( 0.0f, -1500.0f ) );
    scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
    
    RenderSystem::m_layer = HelloWorld::create();
    RenderSystem::m_layer->scheduleUpdate();

    // add layer as a child to scene
    scene->addChild( RenderSystem::m_layer );
    
    Entity* pPlayer = DNASequencer::CreateEntity( "Baked/Characters/Player/player.dna" );
    PhysicsSystem::SetPosition( pPlayer->m_entityHandle, cocos2d::Vec2( 100, 500.0f ) );
    Entity* pFloor = DNASequencer::CreateEntity( "Baked/Characters/Floor/floor.dna" );
    PhysicsSystem::SetPosition( pFloor->m_entityHandle, cocos2d::Vec2( 960.0f, 0.0f ) );
    
    Entity* pLeftWall = DNASequencer::CreateEntity( "Baked/Characters/Wall/wall.dna" );
    PhysicsSystem::SetPosition( pLeftWall->m_entityHandle, cocos2d::Vec2( 0.0f, 0.0f ) );
    Entity* pRightWall = DNASequencer::CreateEntity( "Baked/Characters/Wall/wall.dna" );
    PhysicsSystem::SetPosition( pRightWall->m_entityHandle, cocos2d::Vec2( 1920.0f, 0.0f ) );
    
    
    

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    
    return true;
}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

void HelloWorld::update( float i_dt )
{
    PhysicsSystem::Update( i_dt );
    EntitySystem::Update( i_dt );
    RenderSystem::Update( i_dt );
}
