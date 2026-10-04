// Copyright GCU 2026. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Interaction/SolutionRequirement.h"
#include "Interaction/SolverComponent.h"
#include "UObject/Object.h"
#include "ChildActorClickedRequirement.generated.h"

/**
 * 
 */
UCLASS()
class ATHINGOFTHEPAST_API UChildActorClickedRequirement : public USolutionRequirement
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Config", meta=(AllowedClasses="/Script/Engine.PrimitiveComponent"))
	FComponentReference ComponentReference;
	
	UFUNCTION(BlueprintCallable)
	UActorComponent* GetComponentReference() const
	{
		return ComponentReference.GetComponent(SolverComponentReference->GetOwner());
	}
	
	virtual void BeginPlay_Implementation() override;
	
	UFUNCTION()
	void HandleClicked(UPrimitiveComponent* TouchedComponent, FKey ButtonPressed);
	
	UFUNCTION(BlueprintNativeEvent)
	void OnClicked(UPrimitiveComponent* TouchedComponent, FKey ButtonPressed);
};
