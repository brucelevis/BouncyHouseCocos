//
//  EntitySystem.hpp
//  BouncyHouse
//
//  Created by Derek Peterson on 11/28/15.
//
//

#ifndef EntitySystem_hpp
#define EntitySystem_hpp

#include <iostream>
#include <map>
#include <stdio.h>
#include <vector>

#include "Entity.h"

typedef int EntityHandle;

class EntitySystem
{
private:
    static std::vector<EntityHandle> m_markedForDelete;
    static void RemoveEntity( EntityHandle i_entityHandle );
public:
    static std::map<EntityHandle, Entity*> m_entities;
    static Entity* CreateEntity();
    
    static void MarkForDelete( EntityHandle i_entityHandle );
    static Entity* GetEntity( EntityHandle i_entityHandle );
    
    static void Update( float i_dt );
    
    
    template<typename ComponentType>
    static ComponentType* GetComponent( EntityHandle i_entityHandle )
    {
        Entity* pEntity = EntitySystem::GetEntity( i_entityHandle );
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
};

#endif /* EntitySystem_hpp */
