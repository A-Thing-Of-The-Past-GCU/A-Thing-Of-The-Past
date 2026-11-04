// Copyright GCU 2026. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "PuzzleRequirement.h"
#include "Puzzles/PuzzleSolverComponent.h"
#include "UObject/Object.h"
#include "KeypadRequirement.generated.h"

/**
 * 
 */
UCLASS()
class ATHINGOFTHEPAST_API UKeypadRequirement : public UPuzzleRequirement
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Config", /*meta=(*//*AllowedClasses="/Script/Engine.PrimitiveComponent"), */meta=(GetOptions="GetComponentNames"))
	TMap<int32, FName> KeypadReferences;
	
	UFUNCTION()
	TArray<FString> GetComponentNames() const
	{
		TArray<FString> Options;

		// Get the outer actor component
		const UActorComponent* OwnerComponent =
			GetTypedOuter<UActorComponent>();

		if (!OwnerComponent)
		{
			return Options;
		}

		// Get the actor that owns the component
		AActor* OwnerActor = OwnerComponent->GetOwner();

		if (!OwnerActor)
		{
			return Options;
		}

		// Get all components on the actor
		TArray<UActorComponent*> Components;
		OwnerActor->GetComponents(Components);

		for (const UActorComponent* Component : Components)
		{
			if (Component)
			{
				Options.Add(Component->GetName());
			}
		}

		return Options;
	}

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Config")
	TMap<AActor*, int32> KeypadPointers;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Config")
	TArray<int32> DesiredKeypadOutput;
	
	virtual void BeginPlay_Implementation() override;

protected:
	
	UFUNCTION()
	void HandleClicked(AActor* TouchedActor , FKey ButtonPressed);
	
	UFUNCTION(BlueprintNativeEvent)
	void OnClicked(AActor* TouchedActor , FKey ButtonPressed);
	
	UPROPERTY()
	TArray<int32> CurrentKeypadOutput;
};
