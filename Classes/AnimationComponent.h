//
//  AnimationComponent.hpp
//  BouncyHouse
//
//  Created by Derek Peterson on 12/2/15.
//
//

#ifndef AnimationComponent_hpp
#define AnimationComponent_hpp

#include "cocos2d.h"

#include "Component.h"
#include "LocomotionMode.h"
#include "TypeDefs.h"

class AnimationComponent : public Component
{
private:
    std::map<std::string, MotionInfo> m_motions;
    std::string m_currentMotionName;
public:
    static std::string s_componentType;
    
    AnimationComponent() {};
    virtual ~AnimationComponent();
    
    void Init( EntityHandle i_entityHandle, const rapidjson::Value& i_dnaObject );
    void Activate();
    
    void StartMotion( std::string i_motionName, float i_loops = 1 );
    void SyncMotionRate();
    
    MotionInfo GetCurrentMotion() { return m_motions.at( m_currentMotionName ); };
    std::string GetCurrentMotionName() { return m_currentMotionName; };
};

#endif /* AnimationComponent_hpp */
