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
public:
    static LightingSystem* GetInstance();
    void DestroyInstance();
    
    void Update( float i_dt );
    
    std::map<EntityHandle, Component*> m_components;
    void RegisterComponent( Component* i_component );
    void UnregisterComponent( Component* i_component );
    
    void AddLightEffect( LightEffect* i_lightEffect );
    void RemoveLightEffect( LightEffect* i_lightEffect );
    std::vector<LightEffect*> GetLightEffects() { return m_lightEffects; };
    
    cocos2d::GLProgramState* GetGLProgramState();
    
    bool GetDebug() { return m_debug; };
    void SetDebug( bool i_debug ) { m_debug = i_debug; };
private:
    static LightingSystem* s_instance;
    bool m_debug;
    
    std::vector<LightEffect*> m_lightEffects;
    cocos2d::GLProgramState* m_GLProgramState;
};

#endif /* LightingSystem_hpp */
