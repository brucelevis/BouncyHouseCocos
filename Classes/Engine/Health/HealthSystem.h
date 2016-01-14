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
    static HealthSystem* GetInstance();
    static void DestroyInstance();
    
    void Update( float i_dt );
    
    std::map<EntityHandle, Component*> m_components;
    void RegisterComponent( Component* i_component );
    void UnregisterComponent( Component* i_component );
    
    void DNADataInit();
    
    bool GetDebug() { return m_debug; };
    void SetDebug( bool i_debug ) { m_debug = i_debug; };
private:
    static HealthSystem* s_instance;
    bool m_debug;
};

#endif /* HealthSystem_hpp */
