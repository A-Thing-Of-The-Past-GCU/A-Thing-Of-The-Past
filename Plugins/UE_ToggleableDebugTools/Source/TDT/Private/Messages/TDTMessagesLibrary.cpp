// // Copyright Kara Brown 2026. All Rights Reserved.
//
//
#include "Messages/TDTMessagesLibrary.h"

#include "Kismet/KismetSystemLibrary.h"

TMap<FGameplayTag, FDebugOutputSettingsChangedMulticast>	UTDTMessagesLibrary::DebugSettingsChangedEvents;

void UTDTMessagesLibrary::Print(
	const UObject* Outer, 
	const FString String, 
	FGameplayTag Tag,
	const TDTVerbosityLevel Verbosity, 
	const FName Key
)
{
	const auto OutputConfig = TDTConfig::GetMutableOutputConfig();
	
	if (Verbosity > OutputConfig->PrintVerbosityLevel && Verbosity > OutputConfig->LogVerbosityLevel)
	{
		return;
	}
	
	if (!Tag.IsValid()) Tag = TAG_DEBUG_Generic;
	const FDebugOutputSettings OutputSettings = OutputConfig->GetOutputSettings(Tag);
	
	if (!OutputSettings.LoggingEnabled && !OutputSettings.PrintingEnabled)
	{
		return;
	}
	
	auto FormattedString = String;
	FormatTPSString(Outer, FormattedString, Tag, Verbosity, NAME_None);
	
	//----------------------------------------------------------------------------------------------------------------------------------------------------------//

	const auto DisplayConfig = TDTConfig::GetMutableDisplayConfig();
	if (!DisplayConfig)
	{
		return;
	}
	
	const FDebugMessageDisplaySettings DisplaySettings =  DisplayConfig->GetMessageDisplaySettings(Tag);
	float Duration = DisplaySettings.Duration;
	FLinearColor Color = DisplaySettings.Color;
	 
	if (const auto VerbositySettings = DisplayConfig->OverrideVerbositySettings.Find(Verbosity))
	{
		switch (VerbositySettings->ColorSettings)
		{
		case DebugMessageDisplaySettingsColor::Override:
			Color = VerbositySettings->ColorOverride;
			break;
		case DebugMessageDisplaySettingsColor::Additive:
			Color += VerbositySettings->ColorAdditive;
			break;
		default:
			break;
		}
		
		if (VerbositySettings->OverrideDuration)
		{
			Duration = VerbositySettings->OverrideDuration;
		}
	}
	
	//----------------------------------------------------------------------------------------------------------------------------------------------------------//
	
	if (OutputSettings.PrintingEnabled && Verbosity <= OutputConfig->PrintVerbosityLevel)
	{
		UKismetSystemLibrary::PrintString(Outer, FormattedString, true, false, Color, Duration, Key);
	}
	if (OutputSettings.LoggingEnabled && Verbosity <= OutputConfig->LogVerbosityLevel)
	{
		Internal_Log(FormattedString, Verbosity);
	}
}

void UTDTMessagesLibrary::Log(const UObject* Outer, const FString String, const FGameplayTag Tag, const TDTVerbosityLevel Verbosity)
{
	const auto OutputConfig = TDTConfig::GetMutableOutputConfig();
	const FDebugOutputSettings OutputSettings = OutputConfig->GetOutputSettings(Tag);
	
	if (!OutputSettings.LoggingEnabled || Verbosity > OutputConfig->LogVerbosityLevel)
	{
		return;
	}
	
	auto FormattedString = String;
	FormatTPSString(Outer, FormattedString, Tag, Verbosity, NAME_None);
	Internal_Log(FormattedString, Verbosity);
}

void UTDTMessagesLibrary::Internal_Log(const FString& String, const TDTVerbosityLevel Verbosity)
{	
	switch (Verbosity)
	{
	case TDTVerbosityLevel::Fatal:
		UE_LOG(LogTDT, Fatal, TEXT("%s"), *String);
		break;
		
	case TDTVerbosityLevel::Error:
		UE_LOG(LogTDT, Error, TEXT("%s"), *String);
		break;

	case TDTVerbosityLevel::Warning:
		UE_LOG(LogTDT, Warning, TEXT("%s"), *String);
		break;

	case TDTVerbosityLevel::Display:
		UE_LOG(LogTDT, Display, TEXT("%s"), *String);
		break;

	case TDTVerbosityLevel::Log:
		UE_LOG(LogTDT, Log, TEXT("%s"), *String);
		break;

	case TDTVerbosityLevel::Verbose:
		UE_LOG(LogTDT, Verbose, TEXT("%s"), *String);
		break;

	case TDTVerbosityLevel::VeryVerbose:
		UE_LOG(LogTDT, VeryVerbose, TEXT("%s"), *String);
		break;

	default:
		UE_LOG(LogTDT, Log, TEXT("%s"), *String);
		break;
	}
}

void UTDTMessagesLibrary::FormatTPSString(
	const UObject* Outer, 
	FString& InString, 
	const FGameplayTag& InTag, 
	const TDTVerbosityLevel InVerbosity, 
	const FName InKey
)
{
	const UTDTOutputConfig* printStringsConfig = TDTConfig::GetMutableOutputConfig();
	if (!printStringsConfig) return;
	
	
	FString HoldPrintKey = "";
	FString HoldVerbosity = "";
	FString HoldContextObject = "";
	FString HoldDebugTag = "";
	FString HoldFrameNumber = "";
	
	
	if(printStringsConfig->DisplayFrameNumber)
	{
		HoldFrameNumber = FString::FromInt(GFrameNumber) + " | ";
	}
	
	if(printStringsConfig->DisplayDebugTag)
	{
		HoldDebugTag = InTag.ToString() + " | ";
	}
	
	if(printStringsConfig->DisplayContextObject)
	{
		if (Outer)
		{
			HoldContextObject = Outer->GetName() + " | ";
		}
		else
		{
			HoldContextObject = "N/A | ";
		}
	}
	
	if(printStringsConfig->DisplayVerbosity)
	{
		HoldVerbosity = StaticEnum<TDTVerbosityLevel>()->GetNameStringByValue(static_cast<int64>(InVerbosity)) + " | ";
	}
	
	if(printStringsConfig->DisplayPrintKey)
	{
		if (!InKey.IsNone())
		{
			HoldPrintKey = InKey.ToString() + " | ";
		}
	}
	
	
	InString = FString::Printf(TEXT("%s%s%s%s%s%s"), *HoldFrameNumber, *HoldVerbosity, *HoldDebugTag, *HoldContextObject, *HoldPrintKey, *InString);
}
