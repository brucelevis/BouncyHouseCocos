//
//  LightingSystem.hpp
//  BouncyHouse
//
//  Created by Derek Peterson on 12/8/15.
//
//

#ifndef LightingSystem_hpp
#define LightingSystem_hpp

#include "cocos2d.h"

#include "../Entity/Component.h"
#include "../../DEFINES.h"
#include "LightEffect.h"
#include "../System/System.h"

class LightingSystem : public System
{
private:
    static std::vector<LightEffect*> m_lightEffects;
    static cocos2d::GLProgramState* m_GLProgramState;
public:
    static void Update( float i_dt );
    
    static std::map<EntityHandle, Component*> m_components;
    static void RegisterComponent( Component* i_component );
    static void UnregisterComponent( Component* i_component );
    
    static void AddLightEffect( LightEffect* i_lightEffect );
    static void RemoveLightEffect( LightEffect* i_lightEffect );
    static std::vector<LightEffect*> GetLightEffects() { return m_lightEffects; };
    
    static cocos2d::GLProgramState* GetGLProgramState();
    
    static bool m_debug;
};

#endif /* LightingSystem_hpp */
