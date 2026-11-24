// Copyright Kara Brown 2026. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
// #include "GameplayTagContainer.h"
#include "GameplayTagContainer.h"
#include "TDTTypes.h"
#include "Components/WidgetComponent.h"
#include "TDTDebugWidgetComponent.generated.h"

struct FTPSDebugValues;

/**
 * 
 */
// struct FGameplayTagContainer;
class UTDTDebugWidget;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent, DisplayName="Debug Text Component"), PrioritizeCategories = "Debug", HideCategories = (Materials, UserInterface, Interaction, Collision, Animation, Physics, Rendering))
class TDT_API UDebugTextWidgetComponent : public UWidgetComponent
{
	GENERATED_BODY()

private:
	
	// UPROPERTY() TObjectPtr<UUserWidget> DebugWidget;

public:
	
	UDebugTextWidgetComponent(const FObjectInitializer& ObjectInitializer);
	
	virtual void BeginPlay() override;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Debug") 
	FGameplayTag DebugTag = TAG_DEBUG_World;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Debug") 
	TSubclassOf<UUserWidget> DebugWidgetClass;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Debug") 
	FText DefaultText = INVTEXT("Debug Text."); 
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Debug") 
	FSlateFontInfo Font;
	
	UFUNCTION(BlueprintCallable, Category = "Toggleable Debug Tools") void SetDebugText(const FText InText);
	UFUNCTION(BlueprintNativeEvent, Category = "Toggleable Debug Tools") void OnDebugValueChanged(const bool DebugDrawEnabled);
	
};
