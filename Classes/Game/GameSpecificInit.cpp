//
//  GameSpecificInit.cpp
//  BouncyHouse
//
//  Created by Derek Peterson on 1/15/16.
//
//

#include "AI/AIBrain/States/DiveBrainState.h"
#include "AI/AIBrain/States/EnemyBraceBrainState.h"
#include "AI/AIBrain/States/EnemyRunBrainState.h"
#include "AI/AIBrain/States/JumpBrainState.h"
#include "AI/AIBrain/States/RunBrainState.h"
#include "AI/AIBrain/States/StunBrainState.h"

#include "GameSpecificInit.h"
#include "../Engine/AI/AISystem.h"
#include "../Engine/Entity/ComponentSystem.h"
#include "../Engine/Locomotion/LocomotionSystem.h"
#include "Stalactite/StalactiteComponent.h"

void GameSpecificInit::Init()
{
    ComponentRegister<StalactiteComponent>( "StalactiteComponent" );
    
    AIBrainStateRegister<DiveBrainState>( "DiveBrainState" );
    AIBrainStateRegister<EnemyRunBrainState>( "EnemyRunBrainState" );
    AIBrainStateRegister<EnemyBraceBrainState>( "EnemyBraceBrainState" );
    AIBrainStateRegister<JumpBrainState>( "JumpBrainState" );
    AIBrainStateRegister<RunBrainState>( "RunBrainState" );
    AIBrainStateRegister<StunBrainState>( "StunBrainState" );
}