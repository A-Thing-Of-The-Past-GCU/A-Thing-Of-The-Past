// Copyright Kara Brown 2026. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
 #include "NativeGameplayTags.h"
#include "TDTTypes.h"
#include "Engine/DeveloperSettings.h"
#include "Blueprint/UserWidget.h"
#include "TDTOutputConfig.generated.h"



UCLASS(config=EditorPerProjectUserSettings, DisplayName = "Toggleable Debug Tools", autoexpandcategories=("Settings"), BlueprintType)
class TDT_API UTDTOutputConfig : public UDeveloperSettings
{
	GENERATED_BODY()
	
	UTDTOutputConfig()
	{
		
		CategoryName = "Plugins";
		SectionName = "Toggleable Debug Tools";
	};
	
public:
	
	UFUNCTION(BlueprintCallable, Category = "Toggleable Debug Tools")
	void SaveTDTConfig()
	{
		SaveConfig();
	}
	
	/** */
	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category="Display", meta=(ForceInlineRow))
	TMap<FGameplayTag, FDebugOutputSettings> OutputSettings;

	/** */
	UPROPERTY(Config, EditAnywhere, BlueprintReadWrite, Category = "Display")
	TDTVerbosityLevel PrintVerbosityLevel = TDT_Display;

	/** */
	UPROPERTY(Config, EditAnywhere, BlueprintReadWrite, Category = "Display")
	TDTVerbosityLevel LogVerbosityLevel = TDT_Log;
	
	/** Whether to include the current frame number in printed and logged messages. */
	UPROPERTY(Config, EditAnywhere, BlueprintReadWrite, Category = "Display|Context")
	bool DisplayFrameNumber = true;

	/** Whether to include the debug tag in printed and logged messages. */
	UPROPERTY(Config, EditAnywhere, BlueprintReadWrite, Category = "Display|Context")
	bool DisplayDebugTag = true;

	/** Whether to include the name of the world context object in printed and logged messages. */
	UPROPERTY(Config, EditAnywhere, BlueprintReadWrite, Category = "Display|Context")
	bool DisplayContextObject = false;

	/** Whether to include the message verbosity in printed and logged messages. */
	UPROPERTY(Config, EditAnywhere, BlueprintReadWrite, Category = "Display|Context")
	bool DisplayVerbosity = false;

	/** Whether to include the print key in printed and logged messages. */
	UPROPERTY(Config, EditAnywhere, BlueprintReadWrite, Category = "Display|Context")
	bool DisplayPrintKey = false;
	
	UPROPERTY(Config)
	bool OverrideDefaultWidgetTextSize = false;
	
	/** */
	UPROPERTY(Config, EditAnywhere, BlueprintReadWrite, Category="World", meta = (EditCondition = "OverrideDefaultWidgetTextSize", SliderExponent = 3, UIMin = 1.0f, UIMax = 50.0f))
	float DefaultWidgetTextSize = 12.0f;
	
	/**Should new DebugTags have their prints enabled by default*/
	UPROPERTY(Config, EditAnywhere, BlueprintReadWrite, Category="Settings")
	bool PrintingEnabledByDefault = true;
	
	/**Should new DebugTags have their logs enabled by default*/
	UPROPERTY(Config, EditAnywhere, BlueprintReadWrite, Category="Settings")
	bool LoggingEnabledByDefault = true;
	
	/** */
	UPROPERTY(Config, EditAnywhere, BlueprintReadWrite, Category="Settings")
	bool DebugDrawingEnabledByDefault = true;
	
	// void Internal_SetOutputSettings(const FGameplayTag InDebugTag, const EDebugEnabled_TDT PrintEnabled = TDT_Undefined, const EDebugEnabled_TDT LoggingEnabled = TDT_Undefined);
	
	FDebugOutputSettings GetOutputSettings(const FGameplayTag& InDebugTag)
	{
		if (const FDebugOutputSettings* Found = OutputSettings.Find(InDebugTag))
		{
			return *Found;
		}
		return UpdateOutputSettings(InDebugTag, TDT_Undefined, TDT_Undefined, TDT_Undefined);
	}
	
	FDebugOutputSettings UpdateOutputSettings(const FGameplayTag& InDebugTag, const EDebugEnabled_TDT bPrintingEnabled = TDT_Undefined, const EDebugEnabled_TDT bLoggingEnabled = TDT_Undefined, const EDebugEnabled_TDT bDrawDebugEnabled = TDT_Undefined)
	{
		if (InDebugTag == FGameplayTag() || !InDebugTag.IsValid())
		{
			return {false};
		}

		if (const auto Found = OutputSettings.Find(InDebugTag))
		{
			Found->PrintingEnabled = bPrintingEnabled == TDT_Undefined ? Found->PrintingEnabled : static_cast<bool>(bPrintingEnabled);
			Found->LoggingEnabled = bLoggingEnabled == TDT_Undefined ? Found->LoggingEnabled : static_cast<bool>(bLoggingEnabled);
			Found->DebugDrawingEnabled = bDrawDebugEnabled == TDT_Undefined ? Found->DebugDrawingEnabled : static_cast<bool>(bDrawDebugEnabled);
			
			SaveConfig();
			return *Found;
		}

		const FDebugOutputSettings New{
			bPrintingEnabled == TDT_Undefined ? PrintingEnabledByDefault : static_cast<bool>(bPrintingEnabled), 
			bLoggingEnabled == TDT_Undefined ? LoggingEnabledByDefault : static_cast<bool>(bLoggingEnabled),
			bDrawDebugEnabled == TDT_Undefined ? DebugDrawingEnabledByDefault : static_cast<bool>(bDrawDebugEnabled)
		};
		
		OutputSettings.Add(InDebugTag, New);
		
		SaveConfig();
		
		return New;
	}
};
