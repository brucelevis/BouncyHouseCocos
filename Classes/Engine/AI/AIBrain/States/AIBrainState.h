//
//  AIBrainState.hpp
//  BouncyHouse
//
//  Created by Derek Peterson on 1/15/16.
//
//

#ifndef AIBrainState_hpp
#define AIBrainState_hpp

#include "../../../../Engine/TypeDefs.h"

class AIBrainState
{
protected:
    EntityHandle m_entityHandle;
public:
    AIBrainState() { };
    virtual ~AIBrainState() { };
    virtual void Init( EntityHandle i_entityHandle ) { m_entityHandle = i_entityHandle; };
    
    virtual void Enter() { };
    virtual void Exit() { };
    
    virtual void OnActivate() { };
    virtual void OnDeactivate() { };
    
    virtual void Update( float i_dt ) { };
};

#endif /* AIBrainState_hpp */
