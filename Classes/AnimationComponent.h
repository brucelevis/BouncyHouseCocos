//
//  AnimationComponent.hpp
//  BouncyHouse
//
//  Created by Derek Peterson on 12/2/15.
//
//

#ifndef AnimationComponent_hpp
#define AnimationComponent_hpp

#include "cocos2d.h"

#include "Component.h"
#include "LocomotionMode.h"
#include "TypeDefs.h"

class AnimationComponent : public Component
{
public:
    static std::string s_componentType;
    
    AnimationComponent() {};
    virtual ~AnimationComponent();
    
    void Init( EntityHandle i_entityHandle, const rapidjson::Value& i_dnaObject );
};

#endif /* AnimationComponent_hpp */
