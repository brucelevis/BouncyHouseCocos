//
//  RenderComponent.hpp
//  BouncyHouse
//
//  Created by Derek Peterson on 11/28/15.
//
//

#ifndef RenderComponent_hpp
#define RenderComponent_hpp

#include <stdio.h>

#include "EffectSprite/EffectSprite.h"
#include "../Entity/Component.h"
#include "../TypeDefs.h"

class RenderComponent : public Component
{
private:
    bool m_facingLeft;
    float m_scale;
    int m_zOrder;
    std::string m_defaultSpriteName;
    std::string m_spriteName;
    std::string m_spriteSheetName;
    std::string m_spriteSheetNormalPath;
public:
    static std::string s_componentType;
    
    RenderComponent() {};
    virtual ~RenderComponent();
    
    virtual void DNADataInit( EntityHandle i_entityHandle, const rapidjson::Value& i_dnaObject ) override;
    virtual void OnActivate() override;
    
    float GetScale();
    void SetScale( float i_scale );
    
    bool GetFacingLeft() { return m_facingLeft; };
    
    EffectSprite* m_sprite;
};

#endif /* RenderComponent_hpp */
