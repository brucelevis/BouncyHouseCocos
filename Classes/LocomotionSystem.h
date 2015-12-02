//
//  LocomotionSystem.hpp
//  BouncyHouse
//
//  Created by Derek Peterson on 12/1/15.
//
//

#ifndef LocomotionSystem_hpp
#define LocomotionSystem_hpp

#include <vector>

#include "cocos2d.h"

#include "Component.h"
#include "DEFINES.h"
#include "LocomotionMode.h"
#include "System.h"

template<typename T> LocomotionMode* createT() { return (LocomotionMode*) new T; }
typedef std::map<std::string, LocomotionMode*(*)()> LocomotionModeMap;

class LocomotionSystem : public System
{
public:
    static void Update( float i_dt );
    
    static std::map<EntityHandle, Component*> m_components;
    static void RegisterComponent( Component* i_component );
    static void UnregisterComponent( Component* i_component );
    
    static void Init();
    static LocomotionMode* CreateLocomotionMode( std::string i_locomotionModeType );
    
    static LocomotionModeMap m_locomotionModeTypes;
    
    static bool m_debug;
};

template<typename T>
struct LocomotionModeRegister : LocomotionSystem {
    LocomotionModeRegister(std::string const& s) {
        LocomotionSystem::m_locomotionModeTypes.insert(std::make_pair(s, &createT<T>));
    }
};

#endif /* LocomotionSystem_hpp */
