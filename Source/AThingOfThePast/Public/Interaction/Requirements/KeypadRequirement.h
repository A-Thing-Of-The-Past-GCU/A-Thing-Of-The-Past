// Copyright GCU 2026. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Interaction/SolutionRequirement.h"
#include "Interaction/SolverComponent.h"
#include "UObject/Object.h"
#include "KeypadRequirement.generated.h"

/**
 * 
 */
UCLASS()
class ATHINGOFTHEPAST_API UKeypadRequirement : public USolutionRequirement
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Config", meta=(AllowedClasses="/Script/Engine.PrimitiveComponent"))
	TMap<int32, FComponentReference> KeypadReferences;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Config")
	TMap<AActor*, int32> KeypadPointers;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Config")
	TArray<int32> DesiredKeypadOutput;

protected:
	
	virtual void BeginPlay_Implementation() override;
	
	UFUNCTION()
	void HandleClicked(AActor* TouchedActor , FKey ButtonPressed);
	
	UFUNCTION(BlueprintNativeEvent)
	void OnClicked(AActor* TouchedActor , FKey ButtonPressed);
	
	UPROPERTY()
	TArray<int32> CurrentKeypadOutput;
};
