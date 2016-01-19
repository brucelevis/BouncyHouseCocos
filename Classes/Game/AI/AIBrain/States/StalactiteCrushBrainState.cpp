//
//  StalactiteCrushBrainState.cpp
//  BouncyHouse
//
//  Created by Derek Peterson on 1/18/16.
//
//

#include "StalactiteCrushBrainState.h"
#include "../../../../Engine/Animation/AnimationSystem.h"
#include "../../../../Engine/Entity/EntitySystem.h"
#include "../../../../Engine/Health/HealthComponent.h"
#include "../../../../Engine/Render/RenderComponent.h"

StalactiteCrushBrainState::StalactiteCrushBrainState()
{
    m_interruptible = false;
}

StalactiteCrushBrainState::~StalactiteCrushBrainState()
{
    
}

void StalactiteCrushBrainState::Enter()
{
    m_timer = 2.0f;
}

void StalactiteCrushBrainState::Exit()
{
    
}

void StalactiteCrushBrainState::OnActivate()
{
    m_active = true;
    
    AnimationSystem::GetInstance()->SendEvent( m_entityHandle, "CRUSH" );
    auto fadeOut = cocos2d::FadeOut::create(2.0f);
    RenderComponent* pRenderComponent = EntitySystem::GetInstance()->GetComponent<RenderComponent>( m_entityHandle );
    if ( pRenderComponent )
    {
        pRenderComponent->m_sprite->runAction(fadeOut);
    }
}

void StalactiteCrushBrainState::OnDeactivate()
{
    m_active = false;
}

void StalactiteCrushBrainState::Update( float i_dt )
{
    m_timer -= i_dt;
    if ( m_timer <= 0.0f )
    {
        HealthComponent* pHealthComponent = EntitySystem::GetInstance()->GetComponent<HealthComponent>( m_entityHandle );
        if ( pHealthComponent )
        {
            pHealthComponent->ChangeHealth( -999999.0f );
        }
    }
}
