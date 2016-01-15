//
//  GameSpecificInit.cpp
//  BouncyHouse
//
//  Created by Derek Peterson on 1/15/16.
//
//

#include "AI/AIBrain/States/DiveBrainState.h"
#include "AI/AIBrain/States/JumpBrainState.h"
#include "AI/AIBrain/States/RunBrainState.h"

#include "GameSpecificInit.h"
#include "../Engine/AI/AISystem.h"
#include "../Engine/Entity/ComponentSystem.h"
#include "../Engine/Locomotion/LocomotionSystem.h"
#include "Stalactite/StalactiteComponent.h"

void GameSpecificInit::Init()
{
    ComponentRegister<StalactiteComponent>( "StalactiteComponent" );
    
    AIBrainStateRegister<DiveBrainState>( "DiveBrainState" );
    AIBrainStateRegister<JumpBrainState>( "JumpBrainState" );
    AIBrainStateRegister<RunBrainState>( "RunBrainState" );
}