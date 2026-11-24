// Copyright Kara Brown 2026. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "NativeGameplayTags.h"

#include "TDTTypes.generated.h"

UE_DECLARE_GAMEPLAY_TAG_EXTERN(TDT_API TAG_DEBUG_Generic);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(TDT_API TAG_DEBUG_Player);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(TDT_API TAG_DEBUG_World);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(TDT_API TAG_DEBUG_AI);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(TDT_API TAG_DEBUG_UI);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(TDT_API TAG_DEBUG_TDT);


DECLARE_LOG_CATEGORY_EXTERN(LogTDT, Log, All);


UENUM(BlueprintType)
enum class TDTVerbosityLevel : uint8
{
	Default UMETA(Hidden),
	Fatal UMETA(ToolTip = "Will crash the editor on called."),
	Error,
	Warning,
	Display,
	Log,
	Verbose,
	VeryVerbose,
};

constexpr TDTVerbosityLevel TDT_Fatal = TDTVerbosityLevel::Fatal;
constexpr TDTVerbosityLevel TDT_Error = TDTVerbosityLevel::Error;
constexpr TDTVerbosityLevel TDT_Warning = TDTVerbosityLevel::Warning;
constexpr TDTVerbosityLevel TDT_Display = TDTVerbosityLevel::Display;
constexpr TDTVerbosityLevel TDT_Log = TDTVerbosityLevel::Log;
constexpr TDTVerbosityLevel TDT_Verbose = TDTVerbosityLevel::Verbose;
constexpr TDTVerbosityLevel TDT_VeryVerbose = TDTVerbosityLevel::VeryVerbose;


enum EDebugEnabled_TDT : uint8
{
	TDT_Disabled = 0,
	TDT_Enabled = 1,
	TDT_Undefined = 2
};


USTRUCT(BlueprintType)
struct FDebugOutputSettings
{
	GENERATED_BODY()
	
public:
	
	/** Whether debug messages are ever printed to the screen. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Debug Output")
	bool PrintingEnabled;
	
	/** Whether debug messages are ever written to the log. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Debug Output")
	bool LoggingEnabled;
	
	/** Whether debug visualizations and drawing are enabled. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Debug Output")
	bool DebugDrawingEnabled;
	
	FDebugOutputSettings()
	{
		PrintingEnabled = false;
		LoggingEnabled = false;
		DebugDrawingEnabled = false;
	}

	FDebugOutputSettings(const bool enabled)
	{
		PrintingEnabled = enabled;
		LoggingEnabled = enabled;
		DebugDrawingEnabled = enabled;
	}
	
	FDebugOutputSettings(const bool bInPrintingEnabled, const bool bInLoggingEnabled, const bool bInDebugDrawingEnabled)
	{
		PrintingEnabled = bInPrintingEnabled;
		LoggingEnabled = bInLoggingEnabled;
		DebugDrawingEnabled = bInDebugDrawingEnabled;
	}
	
};


USTRUCT(BlueprintType)
struct FDebugMessageDisplaySettings
{
	GENERATED_BODY()
	
public:
	
	/** Color used when displaying the debug message. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Debug Output")
	FLinearColor Color = FLinearColor::White;
	
	/** Duration, in seconds, that the debug message remains visible. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Debug Output")
	float Duration = 5.1f;
	
};

UENUM(BlueprintType)
enum class DebugMessageDisplaySettingsColor : uint8
{
	NoOverride,
	Override,
	Additive
};

USTRUCT(BlueprintType)
struct FDebugDisplaySettings_TDT
{
	GENERATED_BODY()

public:
	
	FDebugDisplaySettings_TDT(){}
	
	FDebugDisplaySettings_TDT(const DebugMessageDisplaySettingsColor InColorSettings, const bool InOverrideDuration, const FLinearColor& InColor = FLinearColor::White, const float InDuration = 5.1f)
		: ColorSettings(InColorSettings)
		, OverrideDuration(InOverrideDuration)
		, Duration(InDuration)
	{
		switch (InColorSettings)
		{
		case DebugMessageDisplaySettingsColor::Override:
			ColorOverride = InColor;
			break;
		case DebugMessageDisplaySettingsColor::Additive:
			ColorAdditive = InColor;
			break;
		default:
			break;
		}
	}
	
	/** Determines how the debug message color is modified. */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Settings") DebugMessageDisplaySettingsColor ColorSettings = DebugMessageDisplaySettingsColor::NoOverride;
	
	/** Color to use instead of the message's default color when color overriding is enabled. */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Settings", meta = (EditConditionHides, EditCondition = "ColorSettings==DebugMessageDisplaySettingsColor::Override")) FLinearColor ColorOverride = FLinearColor::White; 
    /** Color to add to the message's existing color when additive color is enabled. */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Settings", meta = (EditConditionHides, EditCondition = "ColorSettings==DebugMessageDisplaySettingsColor::Additive")) FLinearColor ColorAdditive = FLinearColor::Black; 
	
	UPROPERTY() bool OverrideDuration = false;
    /** Duration, in seconds, that the debug message remains visible when duration overriding is enabled. */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Settings", meta = (EditCondition = "OverrideDuration")) float Duration = 5.1f;
};