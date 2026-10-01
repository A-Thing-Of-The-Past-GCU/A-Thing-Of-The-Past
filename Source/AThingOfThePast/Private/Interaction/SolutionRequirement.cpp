// Copyright GCU 2026. All rights reserved.


#include "Interaction/SolutionRequirement.h"

#include "Interaction/SolverComponent.h"

void USolutionRequirement::BeginPlay_Implementation()
{
}

void USolutionRequirement::Internal_BeginPlay(USolverComponent* SolverComponent)
{
	check(this);
	check(IsValid(SolverComponent));
	
	SolverComponentReference = SolverComponent;
	bSolved = bSolvedByDefault;
	BeginPlay();
}
