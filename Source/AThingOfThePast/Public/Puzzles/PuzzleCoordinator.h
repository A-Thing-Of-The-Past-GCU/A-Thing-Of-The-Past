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
	
	/** List of actors that will be listened to. */
	UPROPERTY(BlueprintReadWrite, EditInstanceOnly, Category = Configuration)
	TArray<TObjectPtr<AActor>> PuzzleActors;
	
protected:
	
	/** Internal list of solver components pulled from PuzzleActors. Used for binding to 'OnSolvedChanged' delegate. */
	UPROPERTY(BlueprintReadOnly, Category = Configuration)
	TArray<TObjectPtr<UPuzzleSolverComponent>> SolverComponents;
	
public:
	
	/** List of actors that will be called when completion changed via the IPuzzleSolution interface*/
	UPROPERTY(BlueprintReadWrite, EditInstanceOnly, Category = Configuration)
	TArray<TObjectPtr<AActor>> OutputActors;

	// ----- Solved ----- //
	
	/** Whether the puzzle has been solved. */ 
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool bSolved;
	
	UFUNCTION(BlueprintSetter)
	void SetSolved(bool NewSolved);
	
	UPROPERTY(BlueprintAssignable)
	FOnPuzzleSolvedChanged OnSolvedChanged;
	
	// ----- Editor ----- //

	UPROPERTY(BlueprintReadOnly, Category = Components)
	TObjectPtr<UBillboardComponent> EditorBillboard;
	
	
protected:

	virtual void BeginPlay() override;
	
	UFUNCTION(BlueprintNativeEvent)
	void OnComponentSolvedChanged(bool NewSolved);

};
