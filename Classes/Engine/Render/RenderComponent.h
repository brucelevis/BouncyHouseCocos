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

#include "cocos2d.h"

#include "EffectSprite/EffectSprite.h"
#include "../Entity/Component.h"
#include "../TypeDefs.h"

class RenderComponent : public Component
{
private:
    bool m_facingLeft;
    std::string m_spriteSheetName;
public:
    static std::string s_componentType;
    
    RenderComponent() {};
    virtual ~RenderComponent();
    
    void Init( EntityHandle i_entityHandle, const rapidjson::Value& i_dnaObject );
    
    enum FacingDirection
    {
        NONE,
        LEFT,
        RIGHT
    };
    FacingDirection GetFacing();
    bool SetFacing( FacingDirection i_facingDirection );
    
    bool SetEffect( LightEffect* i_lightEffect );
    
    EffectSprite* m_sprite;
};

#endif /* RenderComponent_hpp */
