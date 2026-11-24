// Copyright Kara Brown 2026. All Rights Reserved.
//
//
#include "Settings/TDTOutputConfig.h"
//
// #include "TDTLibrary.h"
//
// UE_DEFINE_GAMEPLAY_TAG(TAG_DEBUG_Generic, 	"Debug.Generic");
// UE_DEFINE_GAMEPLAY_TAG(TAG_DEBUG_Warning, 	"Debug.Generic.Warning");
// UE_DEFINE_GAMEPLAY_TAG(TAG_DEBUG_Error, 	"Debug.Generic.Error");
// UE_DEFINE_GAMEPLAY_TAG(TAG_DEBUG_Player, 	"Debug.Player");
// UE_DEFINE_GAMEPLAY_TAG(TAG_DEBUG_World, 	"Debug.World");
// UE_DEFINE_GAMEPLAY_TAG(TAG_DEBUG_AI, 		"Debug.AI");
// UE_DEFINE_GAMEPLAY_TAG(TAG_DEBUG_UI, 		"Debug.UI");
//
//
// UTogglePrintStringsConfig::UTogglePrintStringsConfig()
// {
// 	CategoryName = "Debug";
// 	SectionName = "Settings";
// 	
// 	
// 	settings.Add(TAG_DEBUG_Generic, {true, true});
// 	settings.Add(TAG_DEBUG_Player, {true, true});
// 	settings.Add(TAG_DEBUG_World, {true, true});
// }
//
// void UTogglePrintStringsConfig::Internal_SetDebugValues(const FGameplayTag _inDebugTag, const ETPSDebugEnabled _printEnabled, const ETPSDebugEnabled _loggingEnabled)
// {
// 	if (!settings.Contains(_inDebugTag))
// 	{
// 		FTPSDebugValues debugValues;
// 		
// 		if (_printEnabled == ETPSDebugEnabled::Undefined)
// 		{
// 			debugValues.printingEnabled = printingEnabledByDefault;
// 		}
// 		else
// 		{
// 			debugValues.printingEnabled = _printEnabled == ETPSDebugEnabled::Enabled;
// 		}
// 		
// 		if (_loggingEnabled == ETPSDebugEnabled::Undefined)
// 		{
// 			debugValues.loggingEnabled = loggingEnabledByDefault;
// 		}
// 		else
// 		{
// 			debugValues.loggingEnabled = _loggingEnabled == ETPSDebugEnabled::Enabled;
// 		}
// 		
// 		settings.Add(_inDebugTag, debugValues);
// 		SortSettingsAlphabetically(settings);
// 	}
// 	else
// 	{
// 		auto& [printingEnabled, loggingEnabled] = settings.FindChecked(_inDebugTag);
// 		if (_printEnabled != ETPSDebugEnabled::Undefined)
// 		{
// 			printingEnabled = _printEnabled == ETPSDebugEnabled::Enabled;
// 		}
// 		if (_loggingEnabled != ETPSDebugEnabled::Undefined)
// 		{
// 			loggingEnabled = _loggingEnabled == ETPSDebugEnabled::Enabled;
// 		}
// 	}
// 	
// 	SaveConfig();
// }
//
// void UTogglePrintStringsConfig::SortSettingsAlphabetically(TMap<FGameplayTag, FTPSDebugValues>& _settings)
// {
// 	TMap<FGameplayTag, FTPSDebugValues> sortedSettings;
// 	TArray<FGameplayTag> sortedTags;
// 	_settings.GetKeys(sortedTags);
// 	sortedTags.Sort([](const FGameplayTag& _a, const FGameplayTag& _b)
// 	{
// 		return _a.ToString() < _b.ToString();
// 	});
// 	for (FGameplayTag tag : sortedTags)
// 	{
// 		sortedSettings.Add(tag, _settings[tag]);
// 	}
// 	_settings = sortedSettings;
// }
