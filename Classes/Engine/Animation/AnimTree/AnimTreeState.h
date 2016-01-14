//
//  AnimTreeState.hpp
//  BouncyHouse
//
//  Created by Derek Peterson on 1/14/16.
//
//

#ifndef AnimTreeState_hpp
#define AnimTreeState_hpp

#include <stdio.h>
#include "../../../Libraries/rapidjson/document.h"
class AnimTreeState
{
public:
    AnimTreeState();
    ~AnimTreeState();
    void DNADataInit( const rapidjson::Value& i_dnaObject );
    
    bool IsDefault() { return m_defaultState; };
    bool RespondsToEvent( std::string i_event );
    bool IgnoresEvent( std::string i_event );
    std::string GetName() { return m_name; };
    std::string GetExitState() { return m_onExit; };
    std::string GetMotionName() { return m_motionName; };
    bool IsLooping() { return m_loop; };
    
private:
    std::string m_name;
    bool m_defaultState;
    std::string m_motionName;
    bool m_loop;
    std::string m_onExit;
    std::vector<std::string> m_events;
    std::vector<std::string> m_ignoreEvents;
};

#endif /* AnimTreeState_hpp */
