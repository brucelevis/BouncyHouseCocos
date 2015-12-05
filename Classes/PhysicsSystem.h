//
//  PhysicsSystem.hpp
//  BouncyHouse
//
//  Created by Derek Peterson on 11/28/15.
//
//

#ifndef PhysicsSystem_hpp
#define PhysicsSystem_hpp

#include <stdio.h>

#include "System.h"

class PhysicsSystem : public System
{
public:
    static void Init();
    static void Update( float i_dt );
    
    static std::map<EntityHandle, Component*> m_components;
    static void RegisterComponent( Component* i_component );
    static void UnregisterComponent( Component* i_component );
    
    static bool SetPosition( EntityHandle i_entityHandle, cocos2d::Vec2 i_position );
    
    static CollisionCategory GetCollisionCategory( std::string i_collisionCategory );
    static bool IsInBitmask( CollisionCategory i_collisionCategory, CollisionCategory i_mask );
    static bool OnContactBegin( cocos2d::PhysicsContact& i_contact );
    static bool OnContactPostSolve( cocos2d::PhysicsContact& i_contact );
    
    static std::map<std::string, CollisionCategory> m_collisionCategoryMap;
    
    static bool m_debug;
};

struct PhysicsContactInfo
{
    EntityHandle m_entityHandle;
    EntityHandle m_otherEntityHandle;
    cocos2d::PhysicsShape* m_shape;
    cocos2d::PhysicsShape* m_otherShape;
    cocos2d::Vec2 m_normal;
    
    PhysicsContactInfo( EntityHandle i_entityHandle, EntityHandle i_otherEntityHandle, cocos2d::PhysicsShape* i_shape, cocos2d::PhysicsShape* i_otherShape, const cocos2d::Vec2 i_normal )
        : m_entityHandle( i_entityHandle ), m_otherEntityHandle( i_otherEntityHandle ), m_shape( i_shape ), m_otherShape( i_otherShape ), m_normal( i_normal ) { };
};

#endif /* PhysicsSystem_hpp */
