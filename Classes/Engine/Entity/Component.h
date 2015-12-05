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

#include "rapidjson/document.h"

#include "../TypeDefs.h"

class Component
{
public:
    static std::string s_componentType;
    
    EntityHandle m_entityHandle;
    
    Component() {};
    virtual ~Component() {};
    
    virtual void Init( EntityHandle i_entityHandle, const rapidjson::Value& i_dnaObject ) {};
    virtual void Activate() {};
};

#endif /* Component_hpp */
