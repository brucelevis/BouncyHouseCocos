//
//  ComponentSystem.cpp
//  BouncyHouse
//
//  Created by Derek Peterson on 11/29/15.
//
//

#include "AnimationComponent.h"
#include "ComponentSystem.h"
#include "GroundDetectComponent.h"
#include "LocomotionComponent.h"
#include "PhysicsComponent.h"
#include "RenderComponent.h"


ComponentMap ComponentSystem::m_componentTypes;

void ComponentSystem::Init()
{
    ComponentRegister<AnimationComponent>( "AnimationComponent" );
    ComponentRegister<GroundDetectComponent>( "GroundDetectComponent" );
    ComponentRegister<LocomotionComponent>( "LocomotionComponent" );
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