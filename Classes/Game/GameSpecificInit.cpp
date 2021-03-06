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
#include "AI/AIBrain/States/EnemySpawnBrainState.h"
#include "AI/AIBrain/States/JumpBrainState.h"
#include "AI/AIBrain/States/RunBrainState.h"
#include "AI/AIBrain/States/StunBrainState.h"

#include "AI/AIBrain/States/StalactiteWiggleBrainState.h"
#include "AI/AIBrain/States/StalactiteFallBrainState.h"
#include "AI/AIBrain/States/StalactiteCrushBrainState.h"

#include "GameSpecificInit.h"
#include "../Engine/AI/AISystem.h"
#include "../Engine/Entity/ComponentSystem.h"
#include "../Engine/Locomotion/LocomotionSystem.h"
#include "Stalactite/StalactiteComponent.h"

void GameSpecificInit::Init()
{
    ComponentRegister<StalactiteComponent>( "StalactiteComponent" );
    
    AIBrainStateRegister<DiveBrainState>( "DiveBrainState" );
    AIBrainStateRegister<EnemyBraceBrainState>( "EnemyBraceBrainState" );
    AIBrainStateRegister<EnemyRunBrainState>( "EnemyRunBrainState" );
    AIBrainStateRegister<EnemySpawnBrainState>( "EnemySpawnBrainState" );
    AIBrainStateRegister<JumpBrainState>( "JumpBrainState" );
    AIBrainStateRegister<RunBrainState>( "RunBrainState" );
    AIBrainStateRegister<StunBrainState>( "StunBrainState" );
    
    AIBrainStateRegister<StalactiteWiggleBrainState>( "StalactiteWiggleBrainState" );
    AIBrainStateRegister<StalactiteFallBrainState>( "StalactiteFallBrainState" );
    AIBrainStateRegister<StalactiteCrushBrainState>( "StalactiteCrushBrainState" );
}