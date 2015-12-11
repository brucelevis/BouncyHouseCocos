//
//  HealthComponent.hpp
//  BouncyHouse
//
//  Created by Derek Peterson on 12/5/15.
//
//

#ifndef HealthComponent_hpp
#define HealthComponent_hpp

#include "../../Libraries/rapidjson/document.h"

#include "../Entity/Component.h"
#include "../TypeDefs.h"

class HealthComponent : public Component
{
private:
    float m_health;
    float m_maxHealth;
    bool m_dying;
public:
    static std::string s_componentType;
    
    HealthComponent() {};
    virtual ~HealthComponent() override;
    
    virtual void DNADataInit( EntityHandle i_entityHandle, const rapidjson::Value& i_dnaObject ) override;
    virtual void OnActivate() override;
    virtual void OnDeactivate() override;
    
    void ChangeHealth( float i_delta ) { m_health += i_delta; };
    
    void BeginDeath();
    void DeathComplete();
    
    float GetHealth() { return m_health; };
    float GetMaxHealth() { return m_maxHealth; };
};

#endif /* HealthComponent_hpp */
