//
//  LocomotionComponent.hpp
//  BouncyHouse
//
//  Created by Derek Peterson on 12/1/15.
//
//

#ifndef LocomotionComponent_hpp
#define LocomotionComponent_hpp

#include "../Entity/Component.h"
#include "LocomotionModes/LocomotionMode.h"
#include "../TypeDefs.h"

class LocomotionComponent : public Component
{
    float m_runSpeed;
    float m_walkSpeed;
    std::string m_locomotionModeName;
public:
    static std::string s_componentType;
    
    LocomotionComponent() {};
    virtual ~LocomotionComponent() override;
    
    virtual void DNADataInit( EntityHandle i_entityHandle, const rapidjson::Value& i_dnaObject ) override;
    virtual void OnActivate() override;
    virtual void OnDeactivate() override;
    
    float GetRunSpeed() { return m_runSpeed; };
    void SetRunSpeed( float i_runSpeed ) { m_runSpeed = i_runSpeed; };
    float GetWalkSpeed() { return m_walkSpeed; };
    void SetWalkSpeed( float i_walkSpeed ) { m_walkSpeed = i_walkSpeed; };
    
    void SetLocomotionMode( std::string i_locomotionModeName );
    
    LocomotionMode* m_locomotionMode;
    JumpState m_jumpState;
};

#endif /* LocomotionComponent_hpp */
