//
//  DebugDrawSystem.hpp
//  BouncyHouse
//
//  Created by Derek Peterson on 1/13/16.
//
//

#ifndef DebugDrawSystem_hpp
#define DebugDrawSystem_hpp


#include <stdio.h>
#include "../System/System.h"
class DebugDrawSystem : public System
{
public:
    static DebugDrawSystem* GetInstance();
    static void DestroyInstance();
    
    void Update( float i_dt );
    
    void DebugDraw( cocos2d::DrawNode* i_drawNode, float i_duration );
    void DebugText( std::string i_text, cocos2d::Vec2 i_position, float i_duration, cocos2d::Color4F i_color = cocos2d::Color4F::WHITE, int i_fontSize = 14, cocos2d::TextHAlignment i_hAlignment = cocos2d::TextHAlignment::CENTER );
    
private:
    static DebugDrawSystem* s_instance;
};


#endif /* DebugDrawSystem_hpp */
