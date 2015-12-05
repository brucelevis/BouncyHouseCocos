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
    
    bool OnContactBegin( cocos2d::PhysicsContact& i_contact );
    bool OnContactPostSolve( cocos2d::PhysicsContact& i_contact );
    
    cocos2d::EventDispatcher* GetEventDispatcher() { return _eventDispatcher; };
};

#endif /* GameScene_hpp */
