//
//  RunBrainState.hpp
//  BouncyHouse
//
//  Created by Derek Peterson on 1/15/16.
//
//

#ifndef RunBrainState_hpp
#define RunBrainState_hpp

#include "../../../../Engine/AI/AiBrain/States/AIBrainState.h"

class RunBrainState : public AIBrainState
{
protected:
    float m_runDir;
public:
    RunBrainState();
    virtual ~RunBrainState() override;
    
    virtual void Enter() override;
    virtual void Exit() override;
    virtual void OnActivate() override;
    virtual void OnDeactivate() override;
    
    virtual void Update( float i_dt ) override;
    
    float GetMoveDir();
    
    void OnAvatarAction_Jump( cocos2d::EventCustom* i_event );
};

#endif /* RunBrainState_hpp */
