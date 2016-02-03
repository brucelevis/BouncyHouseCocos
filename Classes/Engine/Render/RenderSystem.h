//
//  RenderSystem.hpp
//  BouncyHouse
//
//  Created by Derek Peterson on 11/28/15.
//
//

#ifndef RenderSystem_hpp
#define RenderSystem_hpp

#include <stdio.h>
#include <vector>

#include "cocos2d.h"

#include "../Entity/Component.h"
#include "../../DEFINES.h"
#include "../../Game/Scenes/GameScene.h"
#include "../System/System.h"

class RenderSystem : public System
{
public:
    static RenderSystem* GetInstance();
    static void DestroyInstance();

    void Update( float i_dt );
    
    std::map<EntityHandle, Component*> m_components;
    void RegisterComponent( Component* i_component );
    void UnregisterComponent( Component* i_component );
    
    GameScene* GetScene() { return m_activeScene; };
    void SetScene( GameScene* i_scene ) { m_activeScene = i_scene; };
    
    bool GetDebug() { return m_debug; };
    void SetDebug( bool i_debug ) { m_debug = i_debug; };

private:
    static RenderSystem* s_instance;
    bool m_debug;
    GameScene* m_activeScene;
};

#endif /* RenderSystem_hpp */
