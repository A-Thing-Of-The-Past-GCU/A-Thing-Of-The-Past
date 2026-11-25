// Copyright GCU 2026. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DraggableWidget.generated.h"

class UDraggableComponent;

/**
 * 
 */
UCLASS(Abstract, BlueprintType, Blueprintable)
class ATHINGOFTHEPAST_API UDraggableWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	UDraggableComponent* DraggableComponent = nullptr;
	
};
