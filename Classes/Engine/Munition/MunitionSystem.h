//
//  MunitionSystem.hpp
//  BouncyHouse
//
//  Created by Derek Peterson on 1/15/16.
//
//

#ifndef MunitionSystem_hpp
#define MunitionSystem_hpp

#include "../Entity/Component.h"
#include "../System/System.h"

class MunitionSystem : public System
{
public:
    static MunitionSystem* GetInstance();
    static void DestroyInstance();
    
    void DNADataInit();
    void Update( float i_dt );
    
    std::map<EntityHandle, Component*> m_components;
    void RegisterComponent( Component* i_component );
    void UnregisterComponent( Component* i_component );
    
    bool GetDebug() { return m_debug; };
    void SetDebug( bool i_debug ) { m_debug = i_debug; };
    
    EntityHandle CreateMeleeMunition( EntityHandle m_entityHandle, std::string m_dnaPath );
    void DestroyMunition( EntityHandle i_entityHandle );
    
private:
    static MunitionSystem* s_instance;
    bool m_debug;
};

#endif /* MunitionSystem_hpp */
