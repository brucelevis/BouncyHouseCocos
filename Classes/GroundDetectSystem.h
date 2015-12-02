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

#include "Component.h"
#include "DEFINES.h"
#include "System.h"

class GroundDetectSystem : public System
{
public:
    static void Update( float i_dt );
    
    static std::map<EntityHandle, Component*> m_components;
    static void RegisterComponent( Component* i_component );
    static void UnregisterComponent( Component* i_component );
};

#endif /* GroundDetectSystem_hpp */
