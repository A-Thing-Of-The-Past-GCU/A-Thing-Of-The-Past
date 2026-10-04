// Copyright GCU 2026. All rights reserved.


#include "Interaction/Requirements/ChildActorClickedRequirement.h"

void UChildActorClickedRequirement::BeginPlay_Implementation()
{
	Super::BeginPlay_Implementation();
	
	LOG("Entered: %s", *GetName())
	
	UActorComponent* CompReference = GetComponentReference();
	if (!CompReference)
	{
		LOG("BadCompReference")
		return;
	}
	
	if (const auto PrimitiveComponent = Cast<UPrimitiveComponent>(CompReference))
	{
		LOG("GoodPrimitive %s : %s", *PrimitiveComponent->GetName(), *PrimitiveComponent->GetOwner()->GetName())
		PrimitiveComponent->OnClicked.AddUniqueDynamic(
			this,
			&UChildActorClickedRequirement::HandleClicked
		);
	}
	
	LOG("Exit")
	
}

void UChildActorClickedRequirement::HandleClicked(UPrimitiveComponent* TouchedComponent, FKey ButtonPressed)
{
	OnClicked(TouchedComponent, ButtonPressed);
}

void UChildActorClickedRequirement::OnClicked_Implementation(UPrimitiveComponent* TouchedComponent, FKey ButtonPressed)
{
	LOG("OnClickedCalled: %s, updating solved to %hhd", *GetName(), !bSolved)
	bSolved = !bSolved;
	OnSolvedUpdated.Broadcast(this, bSolved);
}
