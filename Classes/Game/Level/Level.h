//
//  Level.hpp
//  BouncyHouse
//
//  Created by Derek Peterson on 12/4/15.
//
//

#ifndef Level_hpp
#define Level_hpp

#include "cocos2d.h"
#include "../../Engine/Entity/Entity.h"
#include "../../Engine/Render/EffectSprite/LightEffect.h"
#include "../../Engine/TypeDefs.h"

class Level
{
    cocos2d::Vec2 m_playerSpawner;
    cocos2d::Vec2 m_enemySpawner;
    
    Entity* m_player;
    std::map<EntityHandle, Entity*> m_enemies;
    std::map<EntityHandle, Entity*> m_staticEntities;
    int m_maxEnemyCount;
    float m_enemySpawnTimer;
    
    LightEffect* m_lightEffect;
    float m_flickerTimer;
    float m_flickerTime;
    float m_targetBrightness;
    float m_startBrightness;
public:
    Level();
    ~Level();
    
    virtual void update( float i_dt );
    
    Entity* GetPlayer() { return m_player; };
    
    int GetEnemyCount() { return m_enemies.size(); };
    int GetMaxEnemyCount() { return m_maxEnemyCount; };
    
    void SpawnEnemy();
    
    float GetEnemySpawnTimer() { return m_enemySpawnTimer; };
    void SetEnemySpawnTimer( float i_enemySpawnTimer ) { m_enemySpawnTimer = i_enemySpawnTimer; };
    
    void OnRemovingEntityEvent( cocos2d::EventCustom* i_event );
    
    void AddLightEffect( Entity* i_entity );
};

#endif /* Level_hpp */
