//
//  StalactiteComponent.hpp
//  BouncyHouse
//
//  Created by Derek Peterson on 1/9/16.
//
//

#ifndef StalactiteComponent_hpp
#define StalactiteComponent_hpp

#include <stdio.h>
#include "cocos2d.h"

#include "../../Engine/Entity/Component.h"
#include "../../Engine/TypeDefs.h"

class StalactiteComponent : public Component
{
private:
    float m_timer;
    bool m_wiggling;
public:
    static std::string s_componentType;
    
    StalactiteComponent() {};
    virtual ~StalactiteComponent();
    
    virtual void DNADataInit( EntityHandle i_entityHandle, const rapidjson::Value& i_dnaObject ) override;
    virtual void OnActivate() override;
    
    virtual void Update( float i_dt ) override;
    
    void OnGroundChangedEvent( cocos2d::EventCustom* i_event );
};


#endif /* StalactiteComponent_hpp */
