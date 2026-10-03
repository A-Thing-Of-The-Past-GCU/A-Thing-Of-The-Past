// Copyright GCU 2026. All rights reserved.


#include "Interaction/Requirements/KeypadRequirement.h"

#include "Kismet/KismetSystemLibrary.h"

void UKeypadRequirement::BeginPlay_Implementation()
{
	Super::BeginPlay_Implementation();
	
	LOG("Entered: %s", *GetName())

	for (auto [Key, Reference] : KeypadReferences)
	{
		const auto Component = Reference.GetComponent(SolverComponentReference->GetOwner());
		
		if (!Component)
		{
			LOG("BadCompReference: %s", *Reference.ComponentProperty.ToString())
			continue;
		}
	
		
		
		if (const auto ChildActorComponent = Cast<UChildActorComponent>(Component))
		{
			KeypadPointers.Add(ChildActorComponent->GetChildActor(), Key);
			LOG("GoodPrimitive %s : %s", *ChildActorComponent->GetName(), *ChildActorComponent->GetOwner()->GetName())
			ChildActorComponent->GetChildActor()->OnClicked.AddUniqueDynamic(
				this,
				&UKeypadRequirement::HandleClicked);
		}
	
		LOG("Continue")
	}
	
	LOG("Exit")
	
}

void UKeypadRequirement::HandleClicked(AActor* TouchedActor, FKey ButtonPressed)
{
	OnClicked(TouchedActor, ButtonPressed);
}

void UKeypadRequirement::OnClicked_Implementation(AActor* TouchedActor, FKey ButtonPressed)
{
	const auto found = KeypadPointers.Find(TouchedActor);
	if (!found)
	{
		LOG("BadPointer")
		bSolved = false;
		OnSolvedUpdated.Broadcast(this, bSolved);
		CurrentKeypadOutput.Empty();
		return;
	}
	
	FString holdString = FString::Printf(TEXT("Pressed: %d"), *found);
	UKismetSystemLibrary::PrintString(this, holdString);
	
	CurrentKeypadOutput.Add(*found);

	for (int i = 0; i < DesiredKeypadOutput.Num(); ++i)
	{
		if (!CurrentKeypadOutput.IsValidIndex(i))
		{
			LOG("BadSolvedIndex. i: %d, Num: %d", i, CurrentKeypadOutput.Num())
			return;
		}
		
		if (CurrentKeypadOutput[i] != DesiredKeypadOutput[i])
		{
			LOG("BadSolvedKeyPressed. In: %d, Req: %d", CurrentKeypadOutput[i], DesiredKeypadOutput[i])
			bSolved = false;
			OnSolvedUpdated.Broadcast(this, bSolved);
			CurrentKeypadOutput.Empty();
			return;
		}
		
		LOG("Passed: Solve index: %d", i)
	}
	
	LOG("Success!")
	bSolved = true;
	OnSolvedUpdated.Broadcast(this, bSolved);
	
	// LOG("OnClickedCalled: %s, updating solved to %hhd", *GetName(), !bSolved)
	//
	//
	// bSolved = !bSolved;
	// OnSolvedUpdated.Broadcast(this, bSolved);
}
