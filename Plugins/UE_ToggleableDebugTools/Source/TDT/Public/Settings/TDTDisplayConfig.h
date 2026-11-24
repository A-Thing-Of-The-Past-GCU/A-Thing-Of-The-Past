// Copyright Kara Brown 2026. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "TDTTypes.h"
#include "Engine/DeveloperSettings.h"
#include "Blueprint/UserWidget.h"
#include "TDTDisplayConfig.generated.h"



UCLASS(config=ToggleableDebugTools, DefaultConfig, DisplayName = "Toggleable Debug Tools", autoexpandcategories=("Settings"), BlueprintType)
class TDT_API UTDTDisplayConfig : public UDeveloperSettings
{
	GENERATED_BODY()
	
	UTDTDisplayConfig()
	{
		OverrideVerbositySettings = 
		{
			// {TDTVerbosityLevel::Fatal, FDebugDisplaySettings_TDT(true, true, FLinearColor::Black, 1000000.0f)},
			{TDTVerbosityLevel::Error,		FDebugDisplaySettings_TDT(DebugMessageDisplaySettingsColor::Override, false, FLinearColor::Red)},
			{TDTVerbosityLevel::Warning,		FDebugDisplaySettings_TDT(DebugMessageDisplaySettingsColor::Override, false, FLinearColor::Yellow)},
			{TDTVerbosityLevel::Log,			FDebugDisplaySettings_TDT(DebugMessageDisplaySettingsColor::Additive, false, FLinearColor(0.15f, 0.15f, 0.15f))},
			{TDTVerbosityLevel::Verbose,		FDebugDisplaySettings_TDT(DebugMessageDisplaySettingsColor::Additive, false, FLinearColor(0.3f, 0.3f, 0.3f))},
			{TDTVerbosityLevel::VeryVerbose,	FDebugDisplaySettings_TDT(DebugMessageDisplaySettingsColor::Additive, false, FLinearColor(0.45f, 0.45f, 0.45f))}
		};
		
		DebugMenuWidget = TSoftClassPtr<UUserWidget>(FSoftClassPath(TEXT("/TDT/DebugMenuSample/W_DebugMenu_TDT.W_DebugMenu_TDT_C")));
		CategoryName = "Plugins";
		SectionName = "Toggleable Debug Tools";
	};
	
public:
	
	UFUNCTION(BlueprintCallable, Category = "Toggleable Debug Tools")
	void SaveTDTConfig()
	{
		SaveConfig();
	}
	
	/**A Map of Gameplay Tags to debug values, used by the TPS to determine which strings should be printed to screen or to the log, and which should not*/
	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category="Display", meta=(ForceInlineRow))
	TMap<FGameplayTag, FDebugMessageDisplaySettings> PrintSettings;
	
	/** */
	UPROPERTY(Config, EditAnywhere, BlueprintReadWrite, Category="Display", meta=(ForceInlineRow))
	TMap<TDTVerbosityLevel, FDebugDisplaySettings_TDT> OverrideVerbositySettings;
	
	/**The base widget used by TPSCheatManager when spawning the debug menu.*/
	UPROPERTY(Config, EditAnywhere, BlueprintReadWrite, Category="Sample")
	TSoftClassPtr<UUserWidget> DebugMenuWidget;
	
	
	FDebugMessageDisplaySettings GetMessageDisplaySettings(const FGameplayTag& InDebugTag)
	{
		if (const FDebugMessageDisplaySettings* Found = PrintSettings.Find(InDebugTag))
		{
			return *Found;
		}
		const FDebugMessageDisplaySettings Hold = PrintSettings.Add(InDebugTag);
		SaveConfig();
		return Hold;
	}
};
