//
//  HealthSystem.hpp
//  BouncyHouse
//
//  Created by Derek Peterson on 12/5/15.
//
//

#ifndef HealthSystem_hpp
#define HealthSystem_hpp

#include "cocos2d.h"

#include "../Entity/Component.h"
#include "../../DEFINES.h"
#include "../System/System.h"

class HealthSystem : public System
{
public:
    static void Update( float i_dt );
    
    static std::map<EntityHandle, Component*> m_components;
    static void RegisterComponent( Component* i_component );
    static void UnregisterComponent( Component* i_component );
    
    static void Init();    
    static bool m_debug;
};

#endif /* HealthSystem_hpp */
