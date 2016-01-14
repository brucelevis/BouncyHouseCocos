//
//  LightingSystem.cpp
//  BouncyHouse
//
//  Created by Derek Peterson on 12/8/15.
//
//

#include "LightingComponent.h"
#include "LightingSystem.h"

std::map<EntityHandle, Component*> LightingSystem::m_components;
std::vector<LightEffect*> LightingSystem::m_lightEffects;
cocos2d::GLProgramState* LightingSystem::m_GLProgramState;
bool LightingSystem::m_debug;

void LightingSystem::RegisterComponent( Component* i_component )
{
    m_components.insert( std::make_pair( i_component->m_entityHandle, i_component ) );
}

void LightingSystem::UnregisterComponent( Component* i_component )
{
    m_components.erase( i_component->m_entityHandle );
}

void LightingSystem::Update( float i_dt )
{

}

cocos2d::GLProgramState* LightingSystem::GetGLProgramState()
{
    if ( m_GLProgramState )
    {
        return m_GLProgramState;
    }
    else
    {
        auto fileUtiles = cocos2d::FileUtils::getInstance();
        auto fragmentFullPath = fileUtiles->fullPathForFilename( "pointlight.frag" );
        auto fragSource = fileUtiles->getStringFromFile(fragmentFullPath);
        auto glprogram = cocos2d::GLProgram::createWithByteArrays(cocos2d::ccPositionTextureColor_noMVP_vert, fragSource.c_str());

        m_GLProgramState = cocos2d::GLProgramState::getOrCreateWithGLProgram( glprogram );
        m_GLProgramState->retain();

        return m_GLProgramState;
    }
    return NULL;
}

void LightingSystem::AddLightEffect( LightEffect* i_lightEffect )
{
    m_lightEffects.push_back( i_lightEffect );
}

void LightingSystem::RemoveLightEffect( LightEffect* i_lightEffect )
{
    m_lightEffects.erase(std::remove(m_lightEffects.begin(), m_lightEffects.end(), i_lightEffect), m_lightEffects.end());
}
