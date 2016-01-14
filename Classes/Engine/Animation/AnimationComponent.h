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

#include "AnimTree/AnimTree.h"
#include "../Entity/Component.h"
#include "../Locomotion/LocomotionModes/LocomotionMode.h"
#include "../TypeDefs.h"

class AnimationComponent : public Component
{
public:
    static std::string s_componentType;
    
    AnimationComponent() {};
    virtual ~AnimationComponent();
    
    virtual void DNADataInit( EntityHandle i_entityHandle, const rapidjson::Value& i_dnaObject ) override;
    virtual void OnActivate() override;
    virtual void OnDeactivate() override;
    
    void StartMotion( std::string i_motionName, int i_loops = 1 );
    void StopMotion();
    void SyncMotionRate();
    
    MotionInfo GetCurrentMotion() { return m_motions.at( m_currentMotionName ); };
    std::string GetCurrentMotionName() { return m_currentMotionName; };
    
    AnimTree* GetAnimTree() { return m_animTree; };
    
    void OnMotionEnd();

private:
    std::map<std::string, MotionInfo> m_motions;
    std::string m_currentMotionName;
    
    AnimTree* m_animTree;
    
    bool m_motionInterrupted;
};

#endif /* AnimationComponent_hpp */
