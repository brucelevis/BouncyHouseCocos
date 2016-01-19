//
//  AIBrainState.hpp
//  BouncyHouse
//
//  Created by Derek Peterson on 1/15/16.
//
//

#ifndef AIBrainState_hpp
#define AIBrainState_hpp

#include "../../../../Engine/TypeDefs.h"

class AIBrainState
{
protected:
    std::string m_stateName;
protected:
    EntityHandle m_entityHandle;
    bool m_active;
    bool m_interruptible;
public:
    AIBrainState() { m_stateName = "BLANK STATE"; };
    virtual ~AIBrainState() { };
    virtual void Init( EntityHandle i_entityHandle ) { m_entityHandle = i_entityHandle; OnInit(); };
    
    virtual void OnInit() { };
    
    virtual void Enter() { };
    virtual void Exit() { };
    
    virtual void OnActivate() { m_active = true; };
    virtual void OnDeactivate() { m_active = false; };
    
    virtual void Update( float i_dt ) { };
    
    virtual float GetDistanceToEntitySquared( EntityHandle i_entityHandle );
    cocos2d::Vec2 GetDirectionToEntity( EntityHandle i_entityHandle );
    
    bool GetActive() { return m_active; };
    
    void SetStateName( std::string i_stateName ) { m_stateName = i_stateName; };
    std::string GetStateName() { return m_stateName; };
    
    bool GetInterruptible() { return m_interruptible; };
};

#endif /* AIBrainState_hpp */
