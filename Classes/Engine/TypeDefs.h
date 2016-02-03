//
//  TypeDefs.hpp
//  BouncyHouse
//
//  Created by Derek Peterson on 11/28/15.
//
//

#ifndef TypeDefs_hpp
#define TypeDefs_hpp

#include <stdio.h>

typedef int EntityHandle;

// TODO: Somehow we need to be defining these up in game, not in the engine
enum CollisionCategory
{
    None = 0,
    Environment = (1 << 0),
    Solid = (1 << 1),
    Player = (1 << 2),
    Enemy = (1 << 3),
    Bouncy = (1 << 4),
    Munition = (1 << 5),
    Damagable = (1 << 6),
    Ground = (1 << 7),
    All = INT_MAX
};

enum ActionTag : int
{
    AnimationAction
};

enum JumpState
{
    NOT_JUMPING,
    JUMPING,
    FALLING
};

class MotionInfo
{
public:
    std::string m_animationName;
    std::string m_spriteName;
    float m_motionRate;
    int m_startFrame;
    int m_endFrame;
    
    MotionInfo( std::string i_animationName, std::string i_spriteName, float i_motionRate, int i_startFrame, int i_endFrame )
    : m_animationName( i_animationName ), m_spriteName( i_spriteName ), m_motionRate( i_motionRate ), m_startFrame( i_startFrame ), m_endFrame( i_endFrame ) { };
};


#endif /* TypeDefs_hpp */
