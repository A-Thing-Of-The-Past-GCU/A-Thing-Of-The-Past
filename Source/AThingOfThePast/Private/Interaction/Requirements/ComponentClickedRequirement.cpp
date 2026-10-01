// Copyright GCU 2026. All rights reserved.


#include "Interaction/Requirements/ComponentClickedRequirement.h"

void UComponentClickedRequirement::BeginPlay_Implementation()
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
			&UComponentClickedRequirement::HandleClicked
		);
	}
	
	LOG("Exit")
	
}

void UComponentClickedRequirement::HandleClicked(UPrimitiveComponent* TouchedComponent, FKey ButtonPressed)
{
	OnClicked(TouchedComponent, ButtonPressed);
}

void UComponentClickedRequirement::OnClicked_Implementation(UPrimitiveComponent* TouchedComponent, FKey ButtonPressed)
{
	LOG("OnClickedCalled: %s, updating solved to %hhd", *GetName(), !bSolved)
	bSolved = !bSolved;
	OnSolvedUpdated.Broadcast(this, bSolved);
}
