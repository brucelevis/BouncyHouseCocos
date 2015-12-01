//
//  GameScene.hpp
//  BouncyHouse
//
//  Created by Derek Peterson on 11/30/15.
//
//

#ifndef GameScene_hpp
#define GameScene_hpp

#include "cocos2d.h"

class GameScene : public cocos2d::Scene
{
public:
    bool Start();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    virtual void update( float i_dt ) override;
};

#endif /* GameScene_hpp */
