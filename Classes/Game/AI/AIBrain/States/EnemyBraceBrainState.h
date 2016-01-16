//
//  EnemyBraceBrainState.hpp
//  BouncyHouse
//
//  Created by Derek Peterson on 1/15/16.
//
//

#ifndef EnemyBraceBrainState_hpp
#define EnemyBraceBrainState_hpp

#include "../../../../Engine/AI/AiBrain/States/AIBrainState.h"

class EnemyBraceBrainState : public AIBrainState
{
protected:
    EntityHandle m_munitionHandle;
public:
    EnemyBraceBrainState();
    virtual ~EnemyBraceBrainState() override;
    
    virtual void Enter() override;
    virtual void Exit() override;
    virtual void OnActivate() override;
    virtual void OnDeactivate() override;
    
    virtual void Update( float i_dt ) override;
};

#endif /* EnemyBraceBrainState_hpp */
