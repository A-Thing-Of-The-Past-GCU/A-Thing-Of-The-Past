// // Copyright GCU 2026. All rights reserved.
//
//
// #include "Interaction/Requirements/ChildActorClickedRequirement.h"
//
//
// void UChildActorClickedRequirement::BeginPlay_Implementation()
// {
// 	Super::BeginPlay_Implementation();
// 	
// 	LOG("Entered: %s", *GetName())
//
// 	for (auto [Key, Reference] : KeypadReferences)
// 	{
// 		const auto Component = Reference.GetComponent(SolverComponentReference->GetOwner());
// 		
// 		if (!Component)
// 		{
// 			LOG("BadCompReference: %s", *Reference.ComponentProperty.ToString())
// 			continue;
// 		}
// 	
// 		
// 		
// 		if (const auto ChildActorComponent = Cast<UChildActorComponent>(Component))
// 		{
// 			KeypadPointers.Add(ChildActorComponent->GetChildActor(), Key);
// 			LOG("GoodPrimitive %s : %s", *ChildActorComponent->GetName(), *ChildActorComponent->GetOwner()->GetName())
// 			ChildActorComponent->GetChildActor()->OnClicked.AddUniqueDynamic(
// 				this,
// 				&UChildActorClickedRequirement::HandleClicked);
// 		}
// 	
// 		LOG("Continue")
// 	}
// 	
// 	LOG("Exit")
// 	
// }
//
// void UChildActorClickedRequirement::HandleClicked(UPrimitiveComponent* TouchedComponent, FKey ButtonPressed)
// {
// 	OnClicked(TouchedComponent, ButtonPressed);
// }
//
// void UChildActorClickedRequirement::OnClicked_Implementation(UPrimitiveComponent* TouchedComponent, FKey ButtonPressed)
// {
// 	LOG("OnClickedCalled: %s (%s), updating solved to %hhd", *GetName(), *TouchedComponent->GetName(), !bSolved)
// 	bSolved = !bSolved;
// 	OnSolvedUpdated.Broadcast(this, bSolved);
// }
