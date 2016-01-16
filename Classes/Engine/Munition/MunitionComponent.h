//
//  MunitionComponent.hpp
//  BouncyHouse
//
//  Created by Derek Peterson on 1/15/16.
//
//

#ifndef MunitionComponent_hpp
#define MunitionComponent_hpp

#include "cocos2d.h"

#include "../Entity/Component.h"
#include "../TypeDefs.h"

class MunitionComponent : public Component
{
private:
    EntityHandle m_ownerHandle;
    float m_damage;
    std::string m_inflictState;
    bool m_hitOnce;
    std::vector<EntityHandle> m_hitEntities;
public:
    static std::string s_componentType;
    
    MunitionComponent() {};
    virtual ~MunitionComponent() override;
    
    virtual void DNADataInit( EntityHandle i_entityHandle, const rapidjson::Value& i_dnaObject ) override;
    virtual void OnActivate() override;
    virtual void OnDeactivate() override;
    
    virtual void Update( float i_dt ) override;
    
    void MunitionActivate( EntityHandle i_ownerHandle );
    void MunitionDeactivate();
    
    void OnPhysicsContactBeginEvent( cocos2d::EventCustom* i_event );
    void OnRemovingEntityEvent( cocos2d::EventCustom* i_event );
};


#endif /* MunitionComponent_hpp */
