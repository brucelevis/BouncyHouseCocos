#include "HelloWorldScene.h"

#include "EntitySystem.h"
#include "PhysicsComponent.h"
#include "PhysicsSystem.h"
#include "RenderComponent.h"
#include "RenderSystem.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::createWithPhysics();
    scene->getPhysicsWorld()->setGravity( Vec2( 0.0f, -1500.0f ) );
    scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();
    layer->scheduleUpdate();

    // add layer as a child to scene
    scene->addChild(layer);

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

    Entity* pPlayer = EntitySystem::CreateEntity();
    
    RenderComponent* pRenderComponent = new RenderComponent( pPlayer->m_entityHandle );
    pRenderComponent->Init( this );
    pPlayer->m_components.insert( std::make_pair( pRenderComponent->s_componentType, pRenderComponent ) );
    
    PhysicsComponent* pPhysicsComponent = new PhysicsComponent( pPlayer->m_entityHandle );
    pPhysicsComponent->Init();
    pPlayer->m_components.insert( std::make_pair( pPhysicsComponent->s_componentType, pPhysicsComponent ) );
    
    
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
