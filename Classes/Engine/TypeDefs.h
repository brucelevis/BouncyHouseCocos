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
    float m_motionRate;
    
    MotionInfo( std::string i_animationName, float i_motionRate )
    : m_animationName( i_animationName ), m_motionRate( i_motionRate ) { };
};


#endif /* TypeDefs_hpp */
