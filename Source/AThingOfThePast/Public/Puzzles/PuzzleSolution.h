// Copyright GCU 2026. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "PuzzleSolution.generated.h"

UINTERFACE(MinimalAPI)
class UPuzzleSolution : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class ATHINGOFTHEPAST_API IPuzzleSolution
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintNativeEvent)
	void OnPuzzleSolvedUpdated(bool bNewSolved);

};
