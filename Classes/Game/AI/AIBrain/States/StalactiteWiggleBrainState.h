//
//  StalactiteWiggleBrainState.hpp
//  BouncyHouse
//
//  Created by Derek Peterson on 1/18/16.
//
//

#ifndef StalactiteWiggleBrainState_hpp
#define StalactiteWiggleBrainState_hpp

#include "../../../../Engine/AI/AiBrain/States/AIBrainState.h"

class StalactiteWiggleBrainState : public AIBrainState
{
protected:
    EntityHandle m_munitionHandle;
    float m_timer;
public:
    StalactiteWiggleBrainState();
    virtual ~StalactiteWiggleBrainState() override;
    
    virtual void Enter() override;
    virtual void Exit() override;
    virtual void OnActivate() override;
    virtual void OnDeactivate() override;
    
    virtual void Update( float i_dt ) override;
};

#endif /* StalactiteWiggleBrainState_hpp */
