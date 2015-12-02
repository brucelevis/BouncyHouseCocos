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
    
    static std::map<std::string, CollisionCategory> m_collisionCategoryMap;
};

#endif /* PhysicsSystem_hpp */
