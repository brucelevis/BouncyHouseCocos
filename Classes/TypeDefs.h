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
enum CollisionCategory : uint32_t
{
    None = 0,
    Ground = (1 << 0),
    Player = (1 << 1),
    All = INT_MAX
};


#endif /* TypeDefs_hpp */
