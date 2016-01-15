//
//  SideScrollerLocomotionMode.hpp
//  BouncyHouse
//
//  Created by Derek Peterson on 1/15/16.
//
//

#ifndef SideScrollerLocomotionMode_hpp
#define SideScrollerLocomotionMode_hpp

#include "cocos2d.h"

#include "../../TypeDefs.h"
#include "LocomotionMode.h"

class SideScrollerLocomotionMode : public LocomotionMode
{
public:
    SideScrollerLocomotionMode() {};
    virtual ~SideScrollerLocomotionMode() override {};
    
    virtual void Init( EntityHandle i_entityHandle ) override;
    
    virtual void MoveAtSpeed( cocos2d::Vec2 i_moveDir, float i_speed = -1.0f ) override;
    virtual void Update( float i_dt ) override;
};

#endif /* SideScrollerLocomotionMode_hpp */
