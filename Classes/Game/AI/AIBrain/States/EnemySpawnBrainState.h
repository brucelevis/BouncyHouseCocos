//
//  EnemySpawnState.hpp
//  BouncyHouse
//
//  Created by Derek Peterson on 2/3/16.
//
//

#ifndef EnemySpawnState_hpp
#define EnemySpawnState_hpp

#include "../../../../Engine/AI/AiBrain/States/AIBrainState.h"

class EnemySpawnBrainState : public AIBrainState
{
private:
    float m_fadeTimer;
public:
    EnemySpawnBrainState();
    virtual ~EnemySpawnBrainState() override;
    
    virtual void Enter() override;
    virtual void Exit() override;
    virtual void OnActivate() override;
    virtual void OnDeactivate() override;
    
    virtual void Update( float i_dt ) override;
};

#endif /* EnemySpawnState_hpp */
