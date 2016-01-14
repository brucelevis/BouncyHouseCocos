//
//  ComponentSystem.hpp
//  BouncyHouse
//
//  Created by Derek Peterson on 11/29/15.
//
//

#ifndef ComponentSystem_hpp
#define ComponentSystem_hpp

#include <map>
#include <stdio.h>

#include "Component.h"
#include "../System/System.h"

template<typename T> Component* createT() { return (Component*) new T; }
typedef std::map<std::string, Component*(*)()> ComponentMap;

class ComponentSystem : public System
{
public:
    static ComponentSystem* GetInstance();
    static void DestroyInstance();
    
    void DNADataInit();
    Component* CreateComponent( std::string i_componentType );
    ComponentMap m_componentTypes;
    
    bool GetDebug() { return m_debug; };
    void SetDebug( bool i_debug ) { m_debug = i_debug; };
private:
    static ComponentSystem* s_instance;
    bool m_debug;
};

template<typename T>
struct ComponentRegister : ComponentSystem {
    ComponentRegister(std::string const& s) {
        ComponentSystem::GetInstance()->m_componentTypes.insert(std::make_pair(s, &createT<T>));
    }
};

#endif /* ComponentSystem_hpp */
