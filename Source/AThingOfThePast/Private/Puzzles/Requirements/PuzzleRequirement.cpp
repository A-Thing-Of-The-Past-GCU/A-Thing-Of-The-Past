// Copyright GCU 2026. All rights reserved.


#include "Puzzles/Requirements/PuzzleRequirement.h"

#include "Puzzles/PuzzleSolverComponent.h"

void UPuzzleRequirement::BeginPlay_Implementation()
{
}

void UPuzzleRequirement::Internal_BeginPlay(UPuzzleSolverComponent* PuzzleSolverComponent)
{
	check(this);
	check(IsValid(PuzzleSolverComponent));
	
	OwningActor = PuzzleSolverComponent->GetOwner();
	OwningSolverComponent = PuzzleSolverComponent;
	// bSolved = bSolvedByDefault;
	BeginPlay();
}
