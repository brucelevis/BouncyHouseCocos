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
    
    cocos2d::Vec2 m_anchorPoint;
    cocos2d::Vec2 m_offset;
    float m_width;
    float m_height;
    float m_density;
    float m_restitution;
    float m_friction;
    bool m_dynamic;
    
    CollisionCategory m_category;
    CollisionCategory m_collision;
    CollisionCategory m_contact;
    
public:
    static std::string s_componentType;
    
    PhysicsComponent() {};
    virtual ~PhysicsComponent();
    
    void Init( EntityHandle i_entityHandle, const rapidjson::Value& i_dnaObject );
    void Activate();
    
    cocos2d::Node* GetNode() { return m_node; };
    
    cocos2d::Vec2 GetPosition();
    bool SetPosition( cocos2d::Vec2 i_position );
    
    cocos2d::Vec2 GetVelocity();
    float GetWidth() { return m_width; };
    float GetHeight() { return m_height; };
    
    cocos2d::Vec2 GetOffset() { return m_offset; };
    
    CollisionCategory GetCategoryMask() { return m_category; };
    CollisionCategory GetCollisionMask() { return m_collision; };
    CollisionCategory GetContactMask() { return m_contact; };
    
    void ApplyImpulse( cocos2d::Vec2 i_impulse );
    bool RayCast( cocos2d::Vec2 i_start, cocos2d::Vec2 i_end, cocos2d::PhysicsRayCastInfo& o_info );
    
    bool OnContactBegin( cocos2d::PhysicsContact& i_contact );
};

#endif /* PhysicsComponent_hpp */
