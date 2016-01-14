//
//  GroundDetectSystem.hpp
//  BouncyHouse
//
//  Created by Derek Peterson on 12/2/15.
//
//

#ifndef GroundDetectSystem_hpp
#define GroundDetectSystem_hpp

#include "cocos2d.h"

#include "../Entity/Component.h"
#include "../../DEFINES.h"
#include "../System/System.h"

class GroundDetectSystem : public System
{
public:
    static GroundDetectSystem* GetInstance();
    static void DestroyInstance();
    
    void Update( float i_dt );
    
    std::map<EntityHandle, Component*> m_components;
    void RegisterComponent( Component* i_component );
    void UnregisterComponent( Component* i_component );
    
    bool GetDebug() { return m_debug; };
    void SetDebug( bool i_debug ) { m_debug = i_debug; };
private:
    static GroundDetectSystem* s_instance;
    bool m_debug;
};

#endif /* GroundDetectSystem_hpp */
