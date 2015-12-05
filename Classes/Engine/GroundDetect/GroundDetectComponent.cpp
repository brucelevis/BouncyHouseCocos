//
//  GroundDetectComponent.cpp
//  BouncyHouse
//
//  Created by Derek Peterson on 12/2/15.
//
//

#include "GroundDetectComponent.h"
#include "GroundDetectSystem.h"
#include "../Render/RenderComponent.h"

using namespace cocos2d;

std::string GroundDetectComponent::s_componentType = "GroundDetectComponent";

void GroundDetectComponent::Init( EntityHandle i_entityHandle, const rapidjson::Value& i_dnaObject )
{
    m_entityHandle = i_entityHandle;
    GroundDetectSystem::RegisterComponent( this );
}

GroundDetectComponent::~GroundDetectComponent()
{
    GroundDetectSystem::UnregisterComponent( this );
}