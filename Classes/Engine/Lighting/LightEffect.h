#ifndef _LIGHTEFFECT_H_
#define _LIGHTEFFECT_H_

#include "cocos2d.h"

class LightEffect : public cocos2d::Ref
{
public:
    static LightEffect* create();
    
    void setLightPos(const cocos2d::Vec3& pos);
    void setLightColor(const cocos2d::Color3B& color);
    void setBrightness(float value);
    void setLightCutoffRadius(float value);
    void setLightHalfRadius(float value);
    
    void prepareForRender(cocos2d::Sprite *sprite, cocos2d::Texture2D *normalmap, int i_lightNumber);
    
    float getBrightness() { return _brightness; };
    cocos2d::Color3B getLightColor() const { return _lightColor; };
    cocos2d::Vec3 getLightPos() const { return _lightPos; };

protected:
    bool init();

    cocos2d::Vec3 _lightPos;
    cocos2d::Color3B _lightColor;
    float _lightCutoffRadius;
    float _lightHalfRadius;
    float _brightness;
};

#endif
