//
//  LocomotionMode.hpp
//  BouncyHouse
//
//  Created by Derek Peterson on 12/2/15.
//
//

#ifndef LocomotionMode_hpp
#define LocomotionMode_hpp

#include "cocos2d.h"

#include "../../TypeDefs.h"

class LocomotionMode
{
public:
    LocomotionMode() {};
    virtual ~LocomotionMode() {};
    
    virtual void Init( EntityHandle i_entityHandle );
    
    virtual void MoveAtSpeed( cocos2d::Vec2 i_moveDir, float i_speed = -1.0f );
    virtual void Update( float i_dt );
    
    EntityHandle m_entityHandle;
};

#endif /* LocomotionMode_hpp */
