// Copyright GCU 2026. All rights reserved.


#include "Interaction/SolverComponent.h"

USolverComponent::USolverComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void USolverComponent::BeginPlay()
{
	Super::BeginPlay();

	for (const auto Requirement : SolutionRequirements)
	{
		if (!IsValid(Requirement))
		{
			continue;
		}
		
		Requirement->Internal_BeginPlay(this);
		Requirement->OnSolvedUpdated.AddUniqueDynamic(this, &USolverComponent::OnSolutionRequirementsUpdated);
	}
}

void USolverComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void USolverComponent::OnSolutionRequirementsUpdated(const USolutionRequirement* UpdatedRequirement, const bool bSolved)
{
	if (!bSolved)
	{
		OnUnsolved.Broadcast();
		return;
	}
	
	for (const auto Requirement : SolutionRequirements)
	{
		if (!IsValid(Requirement))
		{
			continue;
		}
		
		if (!Requirement->bSolved)
		{
			OnUnsolved.Broadcast();
			return;
		}
	}
	
	OnSolved.Broadcast();
}

