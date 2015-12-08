//
//  GroundDetectComponent.hpp
//  BouncyHouse
//
//  Created by Derek Peterson on 12/2/15.
//
//

#ifndef GroundDetectComponent_hpp
#define GroundDetectComponent_hpp

#include "../Entity/Component.h"
#include "../TypeDefs.h"

class GroundDetectComponent : public Component
{
private:
    bool m_onGround;
public:
    static std::string s_componentType;
    
    GroundDetectComponent() {};
    virtual ~GroundDetectComponent();
    
    void Init( EntityHandle i_entityHandle, const rapidjson::Value& i_dnaObject );
    
    bool GetOnGround() { return m_onGround; };
    void SetOnGround( bool i_onGround ) { m_onGround = i_onGround; };
};

#endif /* GroundDetectComponent_hpp */
