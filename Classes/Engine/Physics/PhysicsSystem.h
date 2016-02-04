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

#include "../System/System.h"

class PhysicsSystem : public System
{
public:
    static PhysicsSystem* GetInstance();
    static void DestroyInstance();
    
    void DNADataInit();
    void Update( float i_dt );
    
    std::map<EntityHandle, Component*> m_components;
    void RegisterComponent( Component* i_component );
    void UnregisterComponent( Component* i_component );
    
    bool SetPosition( EntityHandle i_entityHandle, cocos2d::Vec2 i_position );
    
    CollisionCategory GetCollisionCategory( std::string i_collisionCategory );
    bool IsInBitmask( CollisionCategory i_collisionCategory, CollisionCategory i_mask );
    bool OnContactBegin( cocos2d::PhysicsContact& i_contact );
    bool OnContactPostSolve( cocos2d::PhysicsContact& i_contact );
    
    std::map<std::string, CollisionCategory> m_collisionCategoryMap;
    
    cocos2d::PhysicsWorld* GetPhysicsWorld() { return m_physicsWorld; };
    void SetPhysicsWorld( cocos2d::PhysicsWorld* i_physicsWorld ) { m_physicsWorld = i_physicsWorld; };
    
    bool GetDebug() { return m_debug; };
    void SetDebug( bool i_debug ) { m_debug = i_debug; };
    
private:
    static PhysicsSystem* s_instance;
    cocos2d::PhysicsWorld* m_physicsWorld;
    bool m_debug;
    float m_deathPlaneTimer;
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
