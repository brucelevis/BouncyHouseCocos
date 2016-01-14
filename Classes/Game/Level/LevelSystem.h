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
private:
    static Level* m_level;
    
public:
    static void Update( float i_dt );
    static Level* GetLevel() { return m_level; };
    static void StartLevel( Level* i_level );
};

#endif /* LevelSystem_hpp */
