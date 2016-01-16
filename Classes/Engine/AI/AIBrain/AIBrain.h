//
//  AIBrain.hpp
//  BouncyHouse
//
//  Created by Derek Peterson on 1/15/16.
//
//

#ifndef AIBrain_hpp
#define AIBrain_hpp

#include <stack>
#include "../../../DEFINES.h"
#include "../../TypeDefs.h"
#include "States/AIBrainState.h"

class AIBrain
{
private:
    void PerformPopState();
    void PerformPushState( std::string i_stateName );
    
    std::stack<AIBrainState*> m_states;
    bool m_shouldPop;
    bool m_shouldPush;
    std::string m_pushStateName;
public:
    AIBrain( EntityHandle i_entityHandle );
    ~AIBrain();
    
    void PopState();
    void PushState( std::string i_stateName );
    
    void Update( float i_dt );
    
    AIBrainState* GetCurrentState();
    
    
    EntityHandle m_entityHandle;
};

#endif /* AIBrain_hpp */
