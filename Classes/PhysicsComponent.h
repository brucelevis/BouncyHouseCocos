//
//  PhysicsComponent.hpp
//  BouncyHouse
//
//  Created by Derek Peterson on 11/28/15.
//
//

#ifndef PhysicsComponent_hpp
#define PhysicsComponent_hpp

#include <stdio.h>

#include "cocos2d.h"

#include "Component.h"
#include "TypeDefs.h"

class PhysicsComponent : public Component
{
public:
    static std::string s_componentType;
    
    PhysicsComponent() {};
    PhysicsComponent( EntityHandle i_entityHandle );
    virtual ~PhysicsComponent();
    
    void Init();
    
    
    cocos2d::PhysicsBody* m_physicsBody;
    
};

#endif /* PhysicsComponent_hpp */
