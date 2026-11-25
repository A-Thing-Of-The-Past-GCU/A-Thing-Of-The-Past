// Copyright GCU 2026. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CursorInteractionPromptWidget.generated.h"

/**
 * 
 */
UCLASS(Abstract, BlueprintType, Blueprintable)
class ATHINGOFTHEPAST_API UCursorInteractionPromptWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	TArray<UPrimitiveComponent*> OverlapPrimitives;
	
	void AssignOverlapPrimitive(UPrimitiveComponent* OverlapPrimitive);
	
protected:
	
	UFUNCTION(BlueprintNativeEvent)
	void OnBeginCursorOver(UPrimitiveComponent* TouchedComponent);
	
	UFUNCTION(BlueprintNativeEvent)
	void OnEndCursorOver(UPrimitiveComponent* TouchedComponent);
	
};