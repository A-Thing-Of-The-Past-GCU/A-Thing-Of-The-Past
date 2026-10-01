// Copyright GCU 2026. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "SolutionRequirement.generated.h"


#define LOG(Text, ...) UE_LOG(LogTemp, Log, TEXT(Text), ##__VA_ARGS__);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnLogicSolvedUpdated, const USolutionRequirement*, UpdatedRequirement, bool, bSolved);

UCLASS(Abstract, BlueprintType, EditInlineNew, DefaultToInstanced, Blueprintable)
class ATHINGOFTHEPAST_API USolutionRequirement : public UObject
{
	GENERATED_BODY()
	
public:
	
	UPROPERTY(BlueprintAssignable)
	FOnLogicSolvedUpdated OnSolvedUpdated;
	
	UPROPERTY(BlueprintReadOnly)
	bool bSolved = false;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Config")
	bool bSolvedByDefault = false;

protected:
	
	// Allows USolverComponent to access BeginPlay 
	// without creating a circular dependency
	friend class USolverComponent;
	
	UPROPERTY(BlueprintReadOnly)
	USolverComponent* SolverComponentReference;
	
	UFUNCTION(BlueprintNativeEvent)
	void BeginPlay();
	
private:
	
	void Internal_BeginPlay(USolverComponent* SolverComponent);
	
};
