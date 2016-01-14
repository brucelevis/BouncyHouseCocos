//
//  RunLocomotionMode.hpp
//  BouncyHouse
//
//  Created by Derek Peterson on 12/2/15.
//
//

#ifndef RunLocomotionMode_hpp
#define RunLocomotionMode_hpp

#include "../../../Engine/Locomotion/LocomotionModes/LocomotionMode.h"
#include "../../../Engine/TypeDefs.h"

class RunLocomotionMode : public LocomotionMode
{
private:
    float m_runDir;
    bool m_diving;
public:
    RunLocomotionMode() {};
    virtual ~RunLocomotionMode() override;
    
    virtual void Init( EntityHandle i_entityHandle ) override;
    
    virtual void MoveToPoint( cocos2d::Vec2 i_point, float i_speed ) override;
    virtual void Jump( bool i_force = false, bool i_playAnim = true ) override;
    virtual void Update( float i_dt ) override;

    void OnPhysicsContactBeginEvent( cocos2d::EventCustom* i_event );
    void OnGroundChangedEvent( cocos2d::EventCustom* i_event );
    
    void AfterSmash();
};

#endif /* RunLocomotionMode_hpp */
