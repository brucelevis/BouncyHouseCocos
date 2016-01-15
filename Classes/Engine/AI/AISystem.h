//
//  AISystem.hpp
//  BouncyHouse
//
//  Created by Derek Peterson on 1/15/16.
//
//

#ifndef AISystem_hpp
#define AISystem_hpp

#include <stdio.h>

#include "../Entity/Component.h"
#include "../../DEFINES.h"
#include "../System/System.h"
#include "AIBrain/States/AIBrainState.h"

template<typename T> AIBrainState* createT() { return (AIBrainState*) new T; }
typedef std::map<std::string, AIBrainState*(*)()> AIBrainStateMap;

class AISystem : public System
{
public:
    static AISystem* GetInstance();
    static void DestroyInstance();
    
    void Update( float i_dt );
    
    std::map<EntityHandle, Component*> m_components;
    void RegisterComponent( Component* i_component );
    void UnregisterComponent( Component* i_component );
    
    bool GetDebug() { return m_debug; };
    void SetDebug( bool i_debug ) { m_debug = i_debug; };
    
    AIBrainState* CreateBrainState( std::string i_stateName );
    AIBrainStateMap m_brainStateTypes;
private:
    static AISystem* s_instance;
    bool m_debug;
};

template<typename T>
struct AIBrainStateRegister : AISystem {
    AIBrainStateRegister(std::string const& s) {
        AISystem::GetInstance()->m_brainStateTypes.insert( { s, &createT<T> });
    }
};

#endif /* AISystem_hpp */
