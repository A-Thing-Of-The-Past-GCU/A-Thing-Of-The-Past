// Copyright GCU 2026. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "InteractableInterface.generated.h"

UINTERFACE(MinimalAPI)
class UInteractableInterface : public UInterface
{
	GENERATED_BODY()
};

class ATHINGOFTHEPAST_API IInteractableInterface
{
	GENERATED_BODY()

public:
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	bool CanInteract(AActor* Player);
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	bool AttemptInteract(AActor* Player);
	
	UFUNCTION(BlueprintNativeEvent)
	void OnInteraction(AActor* Player);
};
