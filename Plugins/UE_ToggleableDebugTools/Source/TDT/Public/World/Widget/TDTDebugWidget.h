// Copyright Kara Brown 2026. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "TDTWidgetInterface.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "TDTDebugWidget.generated.h"

UCLASS()
class TDT_API UTDTDebugWidget : public UUserWidget, public ITDTWidgetInterface
{
	GENERATED_BODY()
protected:
	
	virtual void NativeOnInitialized() override;
	
	virtual void NativeConstruct() override;
	
	void OnViewportResized(FViewport* Viewport, uint32 NewSize) const;
	
	UPROPERTY()
	FText DefaultText;
	
public:
	
	UPROPERTY(VisibleAnywhere, Category = "Debug") UTextBlock* TextBlock = nullptr;
	
	virtual void SetDebugText_Implementation(const FText& InText = INVTEXT("Default")) override;
};
