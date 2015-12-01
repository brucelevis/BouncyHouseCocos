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
    Entity* pFloor = DNASequencer::CreateEntity( "Baked/Characters/Floor/floor.dna" );
    
    std::string pTemp = EntitySystem::GetNameDoNotUseInCode( pPlayer->m_entityHandle );

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
