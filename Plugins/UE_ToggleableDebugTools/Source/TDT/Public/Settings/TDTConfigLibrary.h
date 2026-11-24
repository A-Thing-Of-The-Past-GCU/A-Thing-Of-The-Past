// Copyright Kara Brown 2026. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Settings/TDTDisplayConfig.h"
#include "Settings/TDTOutputConfig.h"
#include "TDTConfigLibrary.generated.h"

UCLASS()
class TDT_API UTDTConfigLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	
#pragma region Config
	
	static UTDTOutputConfig* OutputConfigObject;
	static UTDTDisplayConfig* OutputDisplayObject;
	
	/**Returns a MutableDefault UTDTConfig object, changes made require 'SaveConfig' to be called to save.*/
	static const UTDTOutputConfig* GetOutputConfig()
	{
		return GetDefault<UTDTOutputConfig>();
	}
	
	/***/
	static const UTDTDisplayConfig* GetDisplayConfig()
	{
		return GetDefault<UTDTDisplayConfig>();
	}
	
	/**Returns a MutableDefault UTDTConfig object, changes made require 'SaveConfig' to be called to save.*/
	UFUNCTION(BlueprintCallable, Category = "Toggleable Debug Tools|Config", meta = (DevelopmentOnly, ReturnDisplayName = "Config"), DisplayName = "Get Output Config")
	static UTDTOutputConfig* GetMutableOutputConfig()
	{
		if (!OutputConfigObject) OutputConfigObject = GetMutableDefault<UTDTOutputConfig>(); 
		return OutputConfigObject;
	}
	
	/***/
	UFUNCTION(BlueprintCallable, Category = "Toggleable Debug Tools|Config", meta = (DevelopmentOnly, ReturnDisplayName = "Config"), DisplayName = "Get Display Config")
	static UTDTDisplayConfig* GetMutableDisplayConfig()
	{
		if (!OutputDisplayObject) OutputDisplayObject = GetMutableDefault<UTDTDisplayConfig>(); 
		return OutputDisplayObject;
	}
	
#pragma endregion Config
	
	UFUNCTION(BlueprintCallable, Category = "Toggleable Debug Tools|Config", meta = (DevelopmentOnly, ReturnDisplayName = "Settings"))
	static FDebugOutputSettings GetOutputSettings(const FGameplayTag& InDebugTag)
	{
		return GetMutableOutputConfig()->GetOutputSettings(InDebugTag);
	}

	
	UFUNCTION(BlueprintCallable, Category = "Toggleable Debug Tools|Config", meta = (DevelopmentOnly, ReturnDisplayName = "Settings"))
	static FDebugMessageDisplaySettings GetDisplaySettings(const FGameplayTag& InDebugTag)
	{
		return GetMutableDisplayConfig()->GetMessageDisplaySettings(InDebugTag);
	}

};


using TDTConfig = UTDTConfigLibrary;
