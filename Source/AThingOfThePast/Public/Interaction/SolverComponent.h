// Copyright GCU 2026. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "SolutionRequirement.h"
#include "Components/ActorComponent.h"
#include "SolverComponent.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnLogicSolved);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnLogicUnsolved);
// DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnLogicUnsolved, FGameplayTag, UnsolvedTag);


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ATHINGOFTHEPAST_API USolverComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	
	UPROPERTY(BlueprintAssignable)
	FOnLogicSolved OnSolved;
	UPROPERTY(BlueprintAssignable)
	FOnLogicSolved OnUnsolved;
	
	USolverComponent();
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced)
	TArray<TObjectPtr<USolutionRequirement>> SolutionRequirements;
	
	UFUNCTION()
	void OnSolutionRequirementsUpdated(const USolutionRequirement* UpdatedRequirement, bool bSolved);
	
	// TMap<FGameplayTag, USolutionRequirement>
	
	
protected:
	
};
