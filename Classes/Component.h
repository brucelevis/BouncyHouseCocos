//
//  Component.hpp
//  BouncyHouse
//
//  Created by Derek Peterson on 11/28/15.
//
//

#ifndef Component_hpp
#define Component_hpp

#include <stdio.h>

#include "TypeDefs.h"

class Component
{
public:
    static std::string s_componentType;
    
    EntityHandle m_entityHandle;
    
    Component() {};
    Component( EntityHandle i_entityHandle ) {};
    virtual ~Component() {};
    
    virtual void Init() {};
};

#endif /* Component_hpp */
