//
//  AnimationSystem.hpp
//  BouncyHouse
//
//  Created by Derek Peterson on 12/2/15.
//
//

#ifndef AnimationSystem_hpp
#define AnimationSystem_hpp

#include <vector>

#include "cocos2d.h"

#include "../Entity/Component.h"
#include "../../DEFINES.h"
#include "../System/System.h"

class AnimationSystem : public System
{
public:
    static void Update( float i_dt );
    
    static std::map<EntityHandle, Component*> m_components;
    static void RegisterComponent( Component* i_component );
    static void UnregisterComponent( Component* i_component );
    
    static bool m_debug;
};

#endif /* AnimationSystem_hpp */
