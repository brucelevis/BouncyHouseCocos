/****************************************************************************
 Copyright (c) 2014 Chukong Technologies Inc.
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

/*
 * based on cocos2d-x-3.6/tests/cpp-tests/Classes/ShaderTest/ShaderTest2.cpp
 * extended by CodeAndWeb GmbH https://www.codeandweb.com
 */

#include "LightEffect.h"
#include "LightingSystem.h"
#include "EffectSprite.h"

LightEffect* LightEffect::create()
{
    LightEffect *normalMappedSprite = new (std::nothrow) LightEffect();
    if (normalMappedSprite && normalMappedSprite->init())
    {
        normalMappedSprite->autorelease();
        return normalMappedSprite;
    }
    CC_SAFE_DELETE(normalMappedSprite);
    return nullptr;
}

bool LightEffect::init()
{
    if ( LightingSystem::GetGLProgramState() )
    {
        setLightColor(cocos2d::Color3B::WHITE);
        setLightCutoffRadius(500.0f);
        setLightHalfRadius(0.5f);
        return true;
    }
    return false;
}

void LightEffect::setLightPos(const cocos2d::Vec3 &pos)
{
    _lightPos = pos;
}

void LightEffect::setLightColor(const cocos2d::Color3B &color)
{
    _lightColor = color;
}

void LightEffect::setBrightness(float value)
{
    _brightness = value;
}

void LightEffect::setLightCutoffRadius(float value)
{
    _lightCutoffRadius = std::max(1.0f, value);
}

void LightEffect::setLightHalfRadius(float value)
{
    _lightHalfRadius = std::max(0.01f, std::min(0.99f, value));
}

void LightEffect::prepareForRender(cocos2d::Sprite *sprite, cocos2d::Texture2D *normalmap, int i_lightNumber)
{
    auto gl = LightingSystem::GetGLProgramState();

    gl->setUniformVec2("u_contentSize", sprite->getContentSize());

    cocos2d::Point posRelToSpriteOld = PointApplyAffineTransform(cocos2d::Point(_lightPos.x, _lightPos.y), sprite->getWorldToNodeAffineTransform());
    
    cocos2d::Vec2 pPos = sprite->getPosition();
    cocos2d::Point posRelToSprite = cocos2d::Vec2( _lightPos.x, _lightPos.y ) - pPos;
    float zOrder = sprite->getZOrder();
    cocos2d::AffineTransform pTest = sprite->getWorldToNodeAffineTransform();
    cocos2d::Vec2 pAffine = PointApplyAffineTransform( cocos2d::Point( 0.0, 0.0 ), sprite->getWorldToNodeAffineTransform() );

    gl->setUniformTexture("u_normals", normalmap);

    cocos2d::SpriteFrame *frame = sprite->getSpriteFrame();
    cocos2d::Size untrimmedSize = frame->getOriginalSize();
    cocos2d::Size trimmedSize = frame->getRect().size;
    cocos2d::Vec2 framePos = frame->getRect().origin;
    cocos2d::Size texSize = frame->getTexture()->getContentSize();
    
    // set sprite position in sheet
    gl->setUniformVec2("u_spritePosInSheet", cocos2d::Vec2(framePos.x / texSize.width, framePos.y / texSize.height));
    gl->setUniformVec2("u_spriteSizeRelToSheet", cocos2d::Vec2(untrimmedSize.width / texSize.width, untrimmedSize.height / texSize.height));
    gl->setUniformInt("u_spriteRotated", frame->isRotated());
    
    // set offset of trimmed sprite
    cocos2d::Vec2 bottomLeft = frame->getOffset() + (untrimmedSize - trimmedSize) / 2;
    cocos2d::Vec2 cornerOffset = frame->isRotated() ? cocos2d::Vec2(bottomLeft.y, bottomLeft.x)
                                           : cocos2d::Vec2(bottomLeft.x, untrimmedSize.height - trimmedSize.height - bottomLeft.y);
    gl->setUniformVec2("u_spriteOffset", cornerOffset);
    gl->setUniformFloat( "u_zOrder", sprite->getZOrder() );
    
    char pVarName[100];
    sprintf( pVarName, "u_lightActive%d", i_lightNumber );
    gl->setUniformInt( pVarName, 1 );
    sprintf( pVarName, "u_lightPos%d", i_lightNumber );
    gl->setUniformVec3( pVarName, cocos2d::Vec3(posRelToSprite.x, posRelToSprite.y, 0.0 )); //sprite->getZOrder() - _lightPos.z));
    sprintf( pVarName, "u_lightColor%d", i_lightNumber );
    gl->setUniformVec3( pVarName, cocos2d::Vec3(_lightColor.r,_lightColor.g,_lightColor.b)/255.0f);
    sprintf( pVarName, "u_brightness%d", i_lightNumber );
    gl->setUniformFloat( pVarName, _brightness);
    sprintf( pVarName, "u_cutoffRadius%d", i_lightNumber );
    gl->setUniformFloat( pVarName, _lightCutoffRadius);
    sprintf( pVarName, "u_halfRadius%d", i_lightNumber );
    gl->setUniformFloat( pVarName, _lightHalfRadius);

}
