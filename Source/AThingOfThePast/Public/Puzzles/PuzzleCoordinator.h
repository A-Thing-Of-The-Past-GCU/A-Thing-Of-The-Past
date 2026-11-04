// Copyright GCU 2026. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "PuzzleTypes.h"
#include "PuzzleSolverComponent.h"
#include "GameFramework/Actor.h"
#include "PuzzleCoordinator.generated.h"

UCLASS()
class ATHINGOFTHEPAST_API APuzzleCoordinator : public AActor
{
	GENERATED_BODY()
	
public:	
	
	APuzzleCoordinator();
	
	UPROPERTY(BlueprintReadWrite, EditInstanceOnly, Category = Configuration)
	TArray<TObjectPtr<AActor>> PuzzleActors;
	
	UPROPERTY(BlueprintReadOnly, Category = Configuration)
	TArray<TObjectPtr<UPuzzleSolverComponent>> SolverComponents;
	
	UPROPERTY(BlueprintReadWrite, EditInstanceOnly, Category = Configuration)
	TArray<TObjectPtr<AActor>> OutputActors;
	
	// ----- Solved ----- //

	UPROPERTY(BlueprintReadOnly, Category = Components)
	TObjectPtr<UBillboardComponent> EditorBillboard;

	// ----- Solved ----- //
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool bSolved;
	
	UFUNCTION(BlueprintSetter)
	void SetSolved(bool NewSolved);
	
	UPROPERTY(BlueprintAssignable)
	FOnPuzzleSolvedChanged OnSolvedChanged;
	
	
protected:

	virtual void BeginPlay() override;
	
	UFUNCTION(BlueprintNativeEvent)
	void OnComponentSolvedChanged(bool NewSolved);

};
