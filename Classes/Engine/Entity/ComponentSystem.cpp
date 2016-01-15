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

ComponentSystem* ComponentSystem::s_instance;

ComponentSystem* ComponentSystem::GetInstance()
{
    if ( !s_instance )
    {
        s_instance = new ComponentSystem();
    }
    return s_instance;
}

void ComponentSystem::DestroyInstance()
{
    if ( s_instance )
    {
        delete s_instance;
        s_instance = NULL;
    }
}

void ComponentSystem::DNADataInit()
{
    ComponentRegister<AnimationComponent>( "AnimationComponent" );
    ComponentRegister<GroundDetectComponent>( "GroundDetectComponent" );
    ComponentRegister<HealthComponent>( "HealthComponent" );
    ComponentRegister<LightingComponent>( "LightingComponent" );
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