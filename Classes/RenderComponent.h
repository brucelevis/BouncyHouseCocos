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
    RenderComponent( EntityHandle i_entityHandle );
    virtual ~RenderComponent();
    
    void Init( cocos2d::Layer* i_layer );
    
    cocos2d::Sprite* m_sprite;
};

#endif /* RenderComponent_hpp */
