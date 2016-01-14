//
//  AnimTree.hpp
//  BouncyHouse
//
//  Created by Derek Peterson on 1/14/16.
//
//

#ifndef AnimTree_hpp
#define AnimTree_hpp

#include <stdio.h>
#include "AnimTreeState.h"
#include "../../TypeDefs.h"

class AnimTree
{
public:
    AnimTree( EntityHandle i_entityHandle );
    ~AnimTree();
    
    static AnimTree* CreateWithDNA( EntityHandle i_entityHandle, std::string i_fileName );
    void DNADataInit( const rapidjson::Value& i_dnaObject );
    
    void Start();
    void Stop();
    void Update( float i_dt );
    
    void EnterState( AnimTreeState* );
    void ExitState( bool i_interrupted = false );
    
    void SendEvent( std::string i_event );
    
    AnimTreeState* GetDefaultState();
    AnimTreeState* GetState( std::string i_name );
    
    EntityHandle m_entityHandle;
private:
    
    std::map<std::string, AnimTreeState*> m_states;
    
    std::string m_name;
    AnimTreeState* m_activeState;
};

#endif /* AnimTree_hpp */
