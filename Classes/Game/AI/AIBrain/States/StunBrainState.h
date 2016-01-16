//
//  StunBrainState.hpp
//  BouncyHouse
//
//  Created by Derek Peterson on 1/15/16.
//
//

#ifndef StunBrainState_hpp
#define StunBrainState_hpp

#include "../../../../Engine/AI/AiBrain/States/AIBrainState.h"

class StunBrainState : public AIBrainState
{
protected:
    EntityHandle m_munitionHandle;
    float m_timer;
public:
    StunBrainState();
    virtual ~StunBrainState() override;
    
    virtual void Enter() override;
    virtual void Exit() override;
    virtual void OnActivate() override;
    virtual void OnDeactivate() override;
    
    virtual void Update( float i_dt ) override;
};

#endif /* StunBrainState_hpp */
