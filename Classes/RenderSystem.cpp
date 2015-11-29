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
    for ( std::map<EntityHandle, Component*>::iterator it = m_components.begin(); it != m_components.end(); it++ )
    {
        Component* pComponent = it->second;
        //std::cout << "Updating render system for handle: " << pComponent->m_entityHandle << std::endl;
    }
}