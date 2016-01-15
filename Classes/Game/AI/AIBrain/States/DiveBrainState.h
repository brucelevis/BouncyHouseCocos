//
//  DiveBrainState.hpp
//  BouncyHouse
//
//  Created by Derek Peterson on 1/15/16.
//
//

#ifndef DiveBrainState_hpp
#define DiveBrainState_hpp

#include "RunBrainState.h"

class DiveBrainState : public RunBrainState
{
private:
    EntityHandle m_munitionHandle;
public:
    DiveBrainState();
    virtual ~DiveBrainState() override;
    
    virtual void Enter() override;
    virtual void Exit() override;
    virtual void OnActivate() override;
    virtual void OnDeactivate() override;
    
    void OnGroundChangedEvent( cocos2d::EventCustom* i_event );
    void OnMunitionContactEvent( cocos2d::EventCustom* i_event );
};

#endif /* DiveBrainState_hpp */
