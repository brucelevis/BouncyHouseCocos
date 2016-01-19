//
//  StalactiteFallBrainState.hpp
//  BouncyHouse
//
//  Created by Derek Peterson on 1/18/16.
//
//

#ifndef StalactiteFallBrainState_hpp
#define StalactiteFallBrainState_hpp

#include "../../../../Engine/AI/AiBrain/States/AIBrainState.h"

class StalactiteFallBrainState : public AIBrainState
{
protected:
    EntityHandle m_munitionHandle;
public:
    StalactiteFallBrainState();
    virtual ~StalactiteFallBrainState() override;
    
    virtual void Enter() override;
    virtual void Exit() override;
    virtual void OnActivate() override;
    virtual void OnDeactivate() override;
    
    virtual void Update( float i_dt ) override;
    
    void OnGroundChangedEvent( cocos2d::EventCustom* i_event );
};

#endif /* StalactiteFallBrainState_hpp */
