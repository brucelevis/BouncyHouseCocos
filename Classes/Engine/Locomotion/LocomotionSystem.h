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

#include "../Entity/Component.h"
#include "../../DEFINES.h"
#include "LocomotionModes/LocomotionMode.h"
#include "../System/System.h"

template<typename T> LocomotionMode* createT() { return (LocomotionMode*) new T; }
typedef std::map<std::string, LocomotionMode*(*)()> LocomotionModeMap;

class LocomotionSystem : public System
{
public:
    static LocomotionSystem* GetInstance();
    static void DestroyInstance();
    
    void Update( float i_dt );
    
    std::map<EntityHandle, Component*> m_components;
    void RegisterComponent( Component* i_component );
    void UnregisterComponent( Component* i_component );
    
    void DNADataInit();
    LocomotionMode* CreateLocomotionMode( std::string i_locomotionModeType );
    
    LocomotionModeMap m_locomotionModeTypes;
    
    bool GetDebug() { return m_debug; };
    void SetDebug( bool i_debug ) { m_debug = i_debug; };
private:
    static LocomotionSystem* s_instance;
    bool m_debug;
};

template<typename T>
struct LocomotionModeRegister : LocomotionSystem {
    LocomotionModeRegister(std::string const& s) {
        LocomotionSystem::GetInstance()->m_locomotionModeTypes.insert(std::make_pair(s, &createT<T>));
    }
};

#endif /* LocomotionSystem_hpp */
