//
//  RenderSystem.cpp
//  BouncyHouse
//
//  Created by Derek Peterson on 11/28/15.
//
//

#include <iostream>
#include "RenderSystem.h"

std::map<EntityHandle, Component*> RenderSystem::m_components;
cocos2d::Layer* RenderSystem::m_layer;

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
    DebugUpdate( i_dt );
#endif
}

#ifdef DEBUG
void RenderSystem::DebugDraw( cocos2d::DrawNode* i_drawNode, float i_duration )
{
    i_drawNode->runAction( cocos2d::Sequence::create( cocos2d::DelayTime::create( i_duration ), cocos2d::RemoveSelf::create(), nullptr ) );
    RenderSystem::m_layer->addChild( i_drawNode );
}

void RenderSystem::DebugUpdate( float i_dt )
{

}
#endif