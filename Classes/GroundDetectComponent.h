//
//  GroundDetectComponent.hpp
//  BouncyHouse
//
//  Created by Derek Peterson on 12/2/15.
//
//

#ifndef GroundDetectComponent_hpp
#define GroundDetectComponent_hpp

#include "cocos2d.h"

#include "Component.h"
#include "TypeDefs.h"

class GroundDetectComponent : public Component
{
public:
    static std::string s_componentType;
    
    GroundDetectComponent() {};
    virtual ~GroundDetectComponent();
    
    void Init( EntityHandle i_entityHandle, const rapidjson::Value& i_dnaObject );
};

#endif /* GroundDetectComponent_hpp */
