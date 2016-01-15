//
//  EntitySystem.hpp
//  BouncyHouse
//
//  Created by Derek Peterson on 11/28/15.
//
//

#ifndef EntitySystem_hpp
#define EntitySystem_hpp

#include <map>
#include <stdio.h>
#include <vector>

#include "../../Libraries/rapidjson/document.h"

#include "Component.h"
#include "Entity.h"
#include "../../DEFINES.h"
#include "../System/System.h"

typedef int EntityHandle;

class EntitySystem : public System
{
public:
    static EntitySystem* GetInstance();
    static void DestroyInstance();

    Entity* CreateEntity();
    
    void MarkForDelete( EntityHandle i_entityHandle );
    Entity* GetEntity( EntityHandle i_entityHandle );
    
    void Update( float i_dt );
    
    template<typename ComponentType>
    ComponentType* GetComponent( EntityHandle i_entityHandle )
    {
        Entity* pEntity = EntitySystem::GetInstance()->GetEntity( i_entityHandle );
        if ( pEntity->GetBeingDestroyed() )
        {
            return NULL;
        }
        for ( std::map<std::string, Component*>::iterator it = pEntity->m_components.begin(); it != pEntity->m_components.end(); it++ )
        {
            ComponentType* pComponent = dynamic_cast<ComponentType*>( it->second );
            
            if ( pComponent )
            {
                return pComponent;
            }
        }
        return NULL;
    }
    
    Component* AttachAndInitComponent( EntityHandle i_entityHandle, std::string i_componentType, const rapidjson::Value& i_dnaObject );
    Component* AttachComponent( EntityHandle i_entityHandle, std::string i_componentType );
    
#if DEBUG
    static std::string GetNameDoNotUseInCode( EntityHandle i_entityHandle );
#endif
    
    bool GetDebug() { return m_debug; };
    void SetDebug( bool i_debug ) { m_debug = i_debug; };
private:
    static EntitySystem* s_instance;
    bool m_debug;
    
    std::map<EntityHandle, Entity*> m_entities;
    
    std::vector<EntityHandle> m_markedForDelete;
    void RemoveEntity( EntityHandle i_entityHandle );
};

#endif /* EntitySystem_hpp */
