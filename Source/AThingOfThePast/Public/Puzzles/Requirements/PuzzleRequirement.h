// Copyright GCU 2026. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "PuzzleRequirement.generated.h"


#define LOG(Text, ...) UE_LOG(LogTemp, Log, TEXT(Text), ##__VA_ARGS__);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnLogicSolvedUpdated, const UPuzzleRequirement*, UpdatedRequirement, bool, bSolved);

UCLASS(Abstract, BlueprintType, EditInlineNew, DefaultToInstanced, Blueprintable)
class ATHINGOFTHEPAST_API UPuzzleRequirement : public UObject
{
	GENERATED_BODY()
	
public:
	
	UPROPERTY(BlueprintAssignable)
	FOnLogicSolvedUpdated OnSolvedUpdated;
	
	UPROPERTY(BlueprintReadOnly)
	bool bSolved = false;
	
	// UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Config")
	// bool bSolvedByDefault = false;

protected:
	
	// Allows USolverComponent to access BeginPlay 
	// without creating a circular dependency
	friend class UPuzzleSolverComponent;
	
	UPROPERTY(BlueprintReadOnly)
	UPuzzleSolverComponent* OwningSolverComponent;
	
	UPROPERTY(BlueprintReadOnly)
	AActor* OwningActor;
	
	UFUNCTION(BlueprintNativeEvent)
	void BeginPlay();
	
private:
	
	void Internal_BeginPlay(UPuzzleSolverComponent* PuzzleSolverComponent);
	
};
