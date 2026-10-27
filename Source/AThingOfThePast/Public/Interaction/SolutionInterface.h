// Copyright GCU 2026. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "SolverComponent.h"
#include "UObject/Interface.h"
#include "SolutionInterface.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSolutionSolvedUpdated, bool, bSolved);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnSolutionSolved);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnSolutionUnsolved);


UINTERFACE(MinimalAPI)
class USolutionInterface : public UInterface
{
	GENERATED_BODY()
};

class ATHINGOFTHEPAST_API ISolutionInterface
{
	GENERATED_BODY()

public:
	
	//UPROPERTY(BlueprintAssignable)
	FOnSolutionSolvedUpdated OnSolvedUpdated;
	
	//UPROPERTY(BlueprintAssignable)
	FOnSolutionSolved OnSolved;
	
	//UPROPERTY(BlueprintAssignable)
	FOnSolutionUnsolved OnUnsolved;
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	bool GetSolved();
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void RegisterSolver(USolverComponent* SolverComponent);
	
};
