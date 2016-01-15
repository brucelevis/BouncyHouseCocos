//
//  AIComponent.hpp
//  BouncyHouse
//
//  Created by Derek Peterson on 1/15/16.
//
//

#ifndef AIComponent_hpp
#define AIComponent_hpp

#include "../Entity/Component.h"
#include "../TypeDefs.h"
#include "AIBrain.h"

class AIComponent : public Component
{
private:
    AIBrain* m_brain;
public:
    static std::string s_componentType;
    
    AIComponent() {};
    virtual ~AIComponent() override;
    
    virtual void DNADataInit( EntityHandle i_entityHandle, const rapidjson::Value& i_dnaObject ) override;
    virtual void Update( float i_dt ) override;
    
    AIBrain* GetBrain() { return m_brain; };
};

#endif /* AIComponent_hpp */
