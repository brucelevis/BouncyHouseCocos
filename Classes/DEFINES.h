//
//  DEFINES.hpp
//  BouncyHouse
//
//  Created by Derek Peterson on 11/29/15.
//
//

#ifndef DEFINES_hpp
#define DEFINES_hpp

#define GRAVITY -2000.0f
#define JUMP_VELOCITY 17500.0f





#define DEBUG 1
#ifdef DEBUG
    #define DEBUG_NAN 1

    #include <cassert>
    #include <iostream>
    #define ASSERTS( condition, message )                                            \
    {                                                                               \
        if(!(condition))                                                            \
        {                                                                           \
            std::cerr << "Assertion failed at " << __FILE__ << ":" << __LINE__;     \
            std::cerr << " inside " << __FUNCTION__ << std::endl;                   \
            std::cerr << "Condition: " << #condition << std::endl;                  \
            std::cerr << "Message: " << message << std::endl;                       \
            abort();                                                                \
        }                                                                           \
    }
    #define ASSERT( condition )                                                    \
    {                                                                               \
        if(!(condition))                                                            \
        {                                                                           \
            std::cerr << "Assertion failed at " << __FILE__ << ":" << __LINE__;     \
            std::cerr << " inside " << __FUNCTION__ << std::endl;                   \
            std::cerr << "Condition: " << #condition << std::endl;                  \
            abort();                                                                \
        }                                                                           \
    }
#else
    #define ASSERTS( condition, message ) ( condition, message )
    #define ASSERT( condition ) ( condition )
#endif

#endif /* DEFINES_hpp */
