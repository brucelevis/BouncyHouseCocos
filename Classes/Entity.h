//
//  Entity.hpp
//  BouncyHouse
//
//  Created by Derek Peterson on 11/28/15.
//
//

#ifndef Entity_hpp
#define Entity_hpp

#include <stdio.h>
#include <map>

#include "Component.h"
#include "TypeDefs.h"

class Entity
{
public:
    EntityHandle m_entityHandle;
    std::map<std::string, Component*> m_components;
    
    void AddComponent( Component* i_component );
    void RemoveComponent( Component* i_component );
};

#endif /* Entity_hpp */
