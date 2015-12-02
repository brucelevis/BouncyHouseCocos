//
//  RunLocomotionMode.hpp
//  BouncyHouse
//
//  Created by Derek Peterson on 12/2/15.
//
//

#ifndef RunLocomotionMode_hpp
#define RunLocomotionMode_hpp

#include "LocomotionMode.h"
#include "TypeDefs.h"

class RunLocomotionMode : public LocomotionMode
{
public:
    RunLocomotionMode() {};
    virtual ~RunLocomotionMode() {};
    
    virtual void Init( EntityHandle i_entityHandle );
    
    virtual void MoveToPoint( cocos2d::Vec2 i_point, float i_speed );
    virtual void Jump();
    virtual void Update( float i_dt );
};

#endif /* RunLocomotionMode_hpp */
