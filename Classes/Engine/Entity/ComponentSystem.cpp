//
//  ComponentSystem.cpp
//  BouncyHouse
//
//  Created by Derek Peterson on 11/29/15.
//
//

#include "../Animation/AnimationComponent.h"
#include "ComponentSystem.h"
#include "../GroundDetect/GroundDetectComponent.h"
#include "../Health/HealthComponent.h"
#include "../Lighting/LightingComponent.h"
#include "../Locomotion/LocomotionComponent.h"
#include "../Physics/PhysicsComponent.h"
#include "../Render/RenderComponent.h"

// TODO Stop crossing game/engine lines
#include "../../Game/Stalactite/StalactiteComponent.h"


ComponentMap ComponentSystem::m_componentTypes;

void ComponentSystem::DNADataInit()
{
    ComponentRegister<AnimationComponent>( "AnimationComponent" );
    ComponentRegister<GroundDetectComponent>( "GroundDetectComponent" );
    ComponentRegister<HealthComponent>( "HealthComponent" );
    ComponentRegister<LightingComponent>( "LightingComponent" );
    ComponentRegister<LocomotionComponent>( "LocomotionComponent" );
    ComponentRegister<PhysicsComponent>( "PhysicsComponent" );
    ComponentRegister<RenderComponent>( "RenderComponent" );
    
    ComponentRegister<StalactiteComponent>( "StalactiteComponent" );
}

Component* ComponentSystem::CreateComponent( std::string i_componentType )
{
    ComponentMap::iterator it = m_componentTypes.find( i_componentType );
    if ( it == ComponentSystem::m_componentTypes.end() )
        return NULL;
    
    Component* pComponent = it->second();
    return pComponent;
}