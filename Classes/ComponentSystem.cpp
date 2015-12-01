//
//  ComponentSystem.cpp
//  BouncyHouse
//
//  Created by Derek Peterson on 11/29/15.
//
//

#include "ComponentSystem.h"
#include "EntitySystem.h"
#include "PhysicsComponent.h"
#include "RenderComponent.h"


ComponentMap ComponentSystem::m_componentTypes;

void ComponentSystem::Init()
{
    ComponentRegister<PhysicsComponent>( "PhysicsComponent" );
    ComponentRegister<RenderComponent>( "RenderComponent" );
}

Component* ComponentSystem::CreateComponent( std::string i_componentType )
{
    ComponentMap::iterator it = m_componentTypes.find( i_componentType );
    if ( it == ComponentSystem::m_componentTypes.end() )
        return NULL;
    
    Component* pComponent = it->second();
    return pComponent;
}