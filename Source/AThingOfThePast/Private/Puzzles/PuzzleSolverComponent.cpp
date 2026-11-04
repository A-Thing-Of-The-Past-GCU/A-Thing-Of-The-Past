// Copyright GCU 2026. All rights reserved.

#include "Puzzles/PuzzleSolverComponent.h"

#include "Interaction/Requirements/ComponentClickedRequirement.h"

UPuzzleSolverComponent::UPuzzleSolverComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UPuzzleSolverComponent::BeginPlay()
{
	Super::BeginPlay();

	for (const auto Requirement : SolutionRequirements)
	{
		if (!IsValid(Requirement))
		{
			continue;
		}
		
		Requirement->Internal_BeginPlay(this);
		Requirement->OnSolvedUpdated.AddUniqueDynamic(this, &UPuzzleSolverComponent::OnSolutionRequirementsUpdated);
	}
}

void UPuzzleSolverComponent::OnSolutionRequirementsUpdated(const UPuzzleRequirement* UpdatedRequirement, const bool NewSolved)
{	
	// for (const auto Requirement : SolutionRequirements)
	// {
	// 	if (!IsValid(Requirement))
	// 	{
	// 		continue;
	// 	}
	// 	
	// 	if (!Requirement->bSolved)
	// 	{
	// 		OnUnsolved.Broadcast();
	// 		return;
	// 	}
	// }
	//
	// OnSolved.Broadcast();
}

