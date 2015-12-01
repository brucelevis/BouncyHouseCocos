//
//  RenderSystem.hpp
//  BouncyHouse
//
//  Created by Derek Peterson on 11/28/15.
//
//

#ifndef RenderSystem_hpp
#define RenderSystem_hpp

#include <stdio.h>
#include <vector>

#include "cocos2d.h"

#include "Component.h"
#include "DEFINES.h"
#include "System.h"

class RenderSystem : public System
{
public:
    static void Update( float i_dt );
    
    static std::map<EntityHandle, Component*> m_components;
    static void RegisterComponent( Component* i_component );
    static void UnregisterComponent( Component* i_component );
    
    static cocos2d::Scene* m_activeScene;
    
#ifdef DEBUG
    static void DebugDraw( cocos2d::DrawNode* i_drawNode, float i_duration );
    static void DebugUpdate( float i_dt );
#endif
};

#endif /* RenderSystem_hpp */
