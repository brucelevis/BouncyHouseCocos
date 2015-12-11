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

#include "../Entity/Component.h"
#include "../Locomotion/LocomotionModes/LocomotionMode.h"
#include "../TypeDefs.h"

class AnimationComponent : public Component
{
private:
    std::map<std::string, MotionInfo> m_motions;
    std::string m_currentMotionName;
public:
    static std::string s_componentType;
    
    AnimationComponent() {};
    virtual ~AnimationComponent();
    
    virtual void DNADataInit( EntityHandle i_entityHandle, const rapidjson::Value& i_dnaObject ) override;
    virtual void OnActivate() override;
    
    void StartMotion( std::string i_motionName, float i_loops = 1, cocos2d::Action* i_nextAction = NULL );
    void SyncMotionRate();
    
    MotionInfo GetCurrentMotion() { return m_motions.at( m_currentMotionName ); };
    std::string GetCurrentMotionName() { return m_currentMotionName; };
};

#endif /* AnimationComponent_hpp */
