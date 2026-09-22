// Copyright GCU 2026. All rights reserved.


#include "Interaction/Interactable.h"

AInteractable::AInteractable()
{
	
}

void AInteractable::BeginPlay()
{
	Super::BeginPlay();
	
}

bool AInteractable::CanInteract_Implementation(AActor* Player)
{
	return InteractionsEnabled;
}

bool AInteractable::AttemptInteract_Implementation(AActor* Player)
{
	if (!CanInteract_Implementation(Player))
	{
		return false;
	}
	
	OnInteraction_Implementation(Player);
	return true;
}

void AInteractable::OnInteraction_Implementation(AActor* Player)
{
	UE_LOG(LogTemp, Log, TEXT("Interaction started with player (%s)"), *Player->GetName());
	
	if (DisableInteractionsAfterInteraction)
	{
		InteractionsEnabled = false;
	}
	
	if (DestroyAfterInteraction)
	{
		Destroy();
	}
}
