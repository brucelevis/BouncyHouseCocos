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
private:
    cocos2d::PhysicsBody* m_physicsBody;
    cocos2d::Node* m_node;
public:
    static std::string s_componentType;
    
    PhysicsComponent() {};
    virtual ~PhysicsComponent();
    
    void Init( EntityHandle i_entityHandle, const rapidjson::Value& i_dnaObject );
    
    cocos2d::Vec2 GetPosition();
    bool SetPosition( cocos2d::Vec2 i_position );
    
    cocos2d::Vec2 GetVelocity();
    
    void ApplyImpulse( cocos2d::Vec2 i_impulse );
};

#endif /* PhysicsComponent_hpp */
