//
//  EnemyRunBrainState.hpp
//  BouncyHouse
//
//  Created by Derek Peterson on 1/15/16.
//
//

#ifndef EnemyRunBrainState_hpp
#define EnemyRunBrainState_hpp

#include "RunBrainState.h"

class EnemyRunBrainState : public RunBrainState
{
public:
    virtual void Update( float i_dt ) override;
};

#endif /* EnemyRunBrainState_hpp */
