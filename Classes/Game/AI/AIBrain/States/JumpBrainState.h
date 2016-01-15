//
//  JumpBrainState.hpp
//  BouncyHouse
//
//  Created by Derek Peterson on 1/15/16.
//
//

#ifndef JumpBrainState_hpp
#define JumpBrainState_hpp

#include "RunBrainState.h"

class JumpBrainState : public RunBrainState
{
private:
    EntityHandle m_munitionHandle;
public:
    JumpBrainState();
    virtual ~JumpBrainState() override;

    virtual void Enter() override;
    virtual void Exit() override;
    virtual void OnActivate() override;
    virtual void OnDeactivate() override;
    
    void OnGroundChangedEvent( cocos2d::EventCustom* i_event );
    void OnAvatarAction_Jump( cocos2d::EventCustom* i_event );
    void OnMunitionContactEvent( cocos2d::EventCustom* i_event );
};

#endif /* JumpBrainState_hpp */
