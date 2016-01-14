//
//  CaveLevel.hpp
//  BouncyHouse
//
//  Created by Derek Peterson on 1/9/16.
//
//

#ifndef CaveLevel_hpp
#define CaveLevel_hpp

#include <stdio.h>
#include "Level.h"
#include "../../Engine/TypeDefs.h"

class CaveLevel : public Level
{
    virtual void initLevel() override;
    virtual void update( float i_dt ) override;
    
    EntityHandle m_icicleHandle;
};

#endif /* CaveLevel_hpp */
