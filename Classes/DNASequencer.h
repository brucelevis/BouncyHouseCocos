//
//  DNASequencer.hpp
//  BouncyHouse
//
//  Created by Derek Peterson on 11/29/15.
//
//

#ifndef DNASequencer_hpp
#define DNASequencer_hpp

#include <stdio.h>
#include <string>

#include "Entity.h"

class DNASequencer
{
public:
    static Entity* CreateEntity( std::string i_dnaPath );
};

#endif /* DNASequencer_hpp */