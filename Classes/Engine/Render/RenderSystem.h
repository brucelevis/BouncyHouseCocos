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

#include "../Entity/Component.h"
#include "../../DEFINES.h"
#include "../../Game/Scenes/GameScene.h"
#include "../System/System.h"

class RenderSystem : public System
{
public:
    static void Update( float i_dt );
    
    static std::map<EntityHandle, Component*> m_components;
    static void RegisterComponent( Component* i_component );
    static void UnregisterComponent( Component* i_component );
    
    static GameScene* m_activeScene;
    
#ifdef DEBUG
    static void DebugDraw( cocos2d::DrawNode* i_drawNode, float i_duration );
    static void DebugText( std::string i_text, cocos2d::Vec2 i_position, float i_duration, cocos2d::Color4F i_color = cocos2d::Color4F::WHITE, int i_fontSize = 14, cocos2d::TextHAlignment i_hAlignment = cocos2d::TextHAlignment::CENTER );
    static void DebugUpdate( float i_dt );
#endif
};

#endif /* RenderSystem_hpp */
