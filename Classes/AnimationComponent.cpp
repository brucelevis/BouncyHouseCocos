//
//  AnimationComponent.cpp
//  BouncyHouse
//
//  Created by Derek Peterson on 12/2/15.
//
//

#include "AnimationComponent.h"
#include "AnimationSystem.h"
#include "EntitySystem.h"
#include "RenderComponent.h"

using namespace cocos2d;

std::string AnimationComponent::s_componentType = "AnimationComponent";

void AnimationComponent::Init( EntityHandle i_entityHandle, const rapidjson::Value& i_dnaObject )
{
    m_entityHandle = i_entityHandle;
    AnimationSystem::RegisterComponent( this );
    
    RenderComponent* pRenderComponent = EntitySystem::GetComponent<RenderComponent>( m_entityHandle );
    if ( pRenderComponent )
    {
        Vector<SpriteFrame*> pFrames( 18 );
        for ( int i = 0; i < 17; i++ )
        {
            char pFrameName[100] = {0};
            sprintf( pFrameName, "Vik1_Run_%02d.png", i );
            pFrames.pushBack( SpriteFrameCache::getInstance()->getSpriteFrameByName( pFrameName ) );
        }
        
        auto animation = Animation::createWithSpriteFrames( pFrames, 1.0f / 30.0f );
        animation->setLoops( -1 );
        auto animate = Animate::create( animation );
        m_currentAnimation = pRenderComponent->m_sprite->runAction( animate );
    }
}

AnimationComponent::~AnimationComponent()
{
    AnimationSystem::UnregisterComponent( this );
}