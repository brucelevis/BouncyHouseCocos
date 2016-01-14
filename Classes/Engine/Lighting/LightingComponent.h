//
//  LightingComponent.hpp
//  BouncyHouse
//
//  Created by Derek Peterson on 12/8/15.
//
//

#ifndef LightingComponent_hpp
#define LightingComponent_hpp

#include "cocos2d.h"
#include "../../Libraries/rapidjson/document.h"

#include "LightEffect.h"
#include "../Entity/Component.h"
#include "../TypeDefs.h"

class LightingComponent : public Component
{
private:
    LightEffect* m_lightEffect;
    cocos2d::Vec3 m_offset;
public:
    static std::string s_componentType;
    
    LightingComponent() {};
    virtual ~LightingComponent() override;
    
    virtual void Init( EntityHandle i_entityHandle ) override;
    virtual void DNADataInit( EntityHandle i_entityHandle, const rapidjson::Value& i_dnaObject ) override;
    virtual void OnActivate() override;
    virtual void OnDeactivate() override;
    
    virtual void Update( float i_dt ) override;
    
    void SetLightEffect( cocos2d::Vec3 i_offset, float i_brightness, cocos2d::Color3B i_color, float i_radius, float i_halfRadius );
};

#endif /* LightingComponent_hpp */
