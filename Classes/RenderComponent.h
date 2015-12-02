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

#include "Component.h"
#include "TypeDefs.h"

class RenderComponent : public Component
{
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
    
    cocos2d::Sprite* m_sprite;
    cocos2d::SpriteBatchNode* m_spriteBatchNode;
};

#endif /* RenderComponent_hpp */
