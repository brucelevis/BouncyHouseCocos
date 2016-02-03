//
//  RenderSystem.cpp
//  BouncyHouse
//
//  Created by Derek Peterson on 11/28/15.
//
//

#include <iostream>
#include "RenderComponent.h"
#include "RenderSystem.h"
#ifdef DEBUG
#include "DebugDrawSystem.h"
#endif

RenderSystem* RenderSystem::s_instance;

RenderSystem* RenderSystem::GetInstance()
{
    if ( !s_instance )
    {
        s_instance = new RenderSystem();
    }
    return s_instance;
}

void RenderSystem::DestroyInstance()
{
    if ( s_instance )
    {
        delete s_instance;
        s_instance = NULL;
    }
}

void RenderSystem::RegisterComponent( Component* i_component )
{
    m_components.insert( std::make_pair( i_component->m_entityHandle, i_component ) );
}

void RenderSystem::UnregisterComponent( Component* i_component )
{
    m_components.erase( i_component->m_entityHandle );
}

void RenderSystem::Update( float i_dt )
{
#ifdef DEBUG
    if ( m_debug )
    {
        for ( std::map<EntityHandle, Component*>::iterator it = m_components.begin(); it != m_components.end(); it++ )
        {
            RenderComponent* pComponent = (RenderComponent*) it->second;
            if ( pComponent )
            {
                if ( pComponent->m_sprite )
                {
                    cocos2d::DrawNode* pDrawNode = cocos2d::DrawNode::create();
                    pDrawNode->drawPoint( pComponent->m_sprite->getPosition(), 155.0f, cocos2d::Color4F::GREEN );
                    DebugDrawSystem::GetInstance()->DebugDraw( pDrawNode, i_dt * 0.25f );
                }
            }
        }
    }
    
    DebugDrawSystem::GetInstance()->Update( i_dt );
#endif
}
