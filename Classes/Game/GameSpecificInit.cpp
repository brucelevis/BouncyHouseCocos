//
//  GameSpecificInit.cpp
//  BouncyHouse
//
//  Created by Derek Peterson on 1/15/16.
//
//

#include "GameSpecificInit.h"
#include "../Engine/Entity/ComponentSystem.h"
#include "../Engine/Locomotion/LocomotionSystem.h"
#include "Locomotion/LocomotionModes/RunLocomotionMode.h"
#include "Stalactite/StalactiteComponent.h"

void GameSpecificInit::Init()
{
    ComponentRegister<StalactiteComponent>( "StalactiteComponent" );
    
    LocomotionModeRegister<RunLocomotionMode>( "RunLocomotionMode" );
}