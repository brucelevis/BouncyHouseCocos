//
//  StalactiteCrushBrainState.hpp
//  BouncyHouse
//
//  Created by Derek Peterson on 1/18/16.
//
//

#ifndef StalactiteCrushBrainState_hpp
#define StalactiteCrushBrainState_hpp

#include "../../../../Engine/AI/AiBrain/States/AIBrainState.h"

class StalactiteCrushBrainState : public AIBrainState
{
protected:
    EntityHandle m_munitionHandle;
    float m_timer;
public:
    StalactiteCrushBrainState();
    virtual ~StalactiteCrushBrainState() override;
    
    virtual void Enter() override;
    virtual void Exit() override;
    virtual void OnActivate() override;
    virtual void OnDeactivate() override;
    
    virtual void Update( float i_dt ) override;
};

#endif /* StalactiteCrushBrainState_hpp */
