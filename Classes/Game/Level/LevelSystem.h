//
//  LevelSystem.hpp
//  BouncyHouse
//
//  Created by Derek Peterson on 12/4/15.
//
//

#ifndef LevelSystem_hpp
#define LevelSystem_hpp

#include "Level.h"
#include "../../Engine/System/System.h"
class LevelSystem : public System
{
public:
    static void Update( float i_dt );
    
    static Level* m_level;
};

#endif /* LevelSystem_hpp */
