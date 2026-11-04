// Copyright GCU 2026. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "PuzzleTypes.h"
#include "Components/ActorComponent.h"
#include "Requirements/PuzzleRequirement.h"
#include "PuzzleSolverComponent.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ATHINGOFTHEPAST_API UPuzzleSolverComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	
	UPuzzleSolverComponent();
	
	virtual void BeginPlay() override;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool bSolved;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced)
	TArray<TObjectPtr<UPuzzleRequirement>> SolutionRequirements;
	
	UPROPERTY(BlueprintAssignable)
	FOnPuzzleSolvedChanged OnSolvedChanged;
	
protected:
	
	UFUNCTION()
	void OnSolutionRequirementsUpdated(const UPuzzleRequirement* UpdatedRequirement, bool NewSolved);
	
};
