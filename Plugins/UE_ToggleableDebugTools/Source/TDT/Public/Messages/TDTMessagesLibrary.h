// Copyright Kara Brown 2026. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "TDTTypes.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Settings/TDTConfigLibrary.h"
#include "TDTMessagesLibrary.generated.h"



DECLARE_DYNAMIC_DELEGATE_OneParam(FDebugOutputSettingsChangedCallback, /*UObject*, Listener, */const FDebugOutputSettings&, OutputSettings);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDebugOutputSettingsChangedMulticast, /*UObject*, Dispatcher, */const FDebugOutputSettings&, OutputSettings);

#define PRINT(Tag, Verbosity, Text, ...) TDT::Print(this, FString::Printf(TEXT(Text), ##__VA_ARGS__), Tag, Verbosity)
#define PRINT_NAME(Tag, Verbosity, Text, Name, ...) TDT::Print(this, FString::Printf(TEXT(Text), ##__VA_ARGS__), Tag, Verbosity, Name)
#define PRINT_GENERIC(Verbosity, Text, ...) TDT::Print(this, FString::Printf(TEXT(Text), ##__VA_ARGS__), TAG_DEBUG_Generic, Verbosity, Name)

#define PRINT_GLOBAL(Outer, Tag, Verbosity, Text, ...) TDT::Print(Outer, FString::Printf(TEXT(Text), ##__VA_ARGS__), Tag, Verbosity)



UCLASS()
class TDT_API UTDTMessagesLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	
#pragma region Values	
	
#pragma region Values Getters

	/**
	 * Returns whether debug messages for the given tag are printed to the screen.
	 */
	UFUNCTION(BlueprintCallable, Category = "Toggleable Debug Tools|Messages|Settings", meta = (DevelopmentOnly, ReturnDisplayName = "Out"))
	static bool IsDebugPrintingEnabled(UPARAM(meta = (Categories = "Debug")) const FGameplayTag DebugTag)
	{
	    return TDTConfig::GetOutputSettings(DebugTag).PrintingEnabled;
	}

	/**
	 * Returns whether debug messages for the given tag are written to the log.
	 */
	UFUNCTION(BlueprintCallable, Category = "Toggleable Debug Tools|Messages|Settings", meta = (DevelopmentOnly, ReturnDisplayName = "Out"))
	static bool IsDebugLoggingEnabled(UPARAM(meta = (Categories = "Debug")) const FGameplayTag DebugTag)
	{
	    return TDTConfig::GetOutputSettings(DebugTag).LoggingEnabled;
	}
	
#pragma endregion Values Getters
	
#pragma region Values Setters

	/**
	 * Enables or disables screen printing for the given debug tag.
	 */
	UFUNCTION(BlueprintCallable, Category = "Toggleable Debug Tools|Messages|Settings", meta = (DevelopmentOnly))
	static void SetDebugPrintingEnabled(
	    UPARAM(meta = (Categories = "Debug"))
	    const FGameplayTag DebugTag,
	    bool bEnabled
	)
	{
		const auto Config = TDTConfig::GetMutableOutputConfig();
		Config->UpdateOutputSettings(DebugTag, static_cast<EDebugEnabled_TDT>(bEnabled), TDT_Undefined, TDT_Undefined);
		
		if (const auto* FoundDelegates = DebugSettingsChangedEvents.Find(DebugTag))
		{
			FoundDelegates->Broadcast(Config->GetOutputSettings(DebugTag));
		}
	}

	/**
	 * Enables or disables logging for the given debug tag.
	 */
	UFUNCTION(BlueprintCallable, Category = "Toggleable Debug Tools|Messages|Settings", meta = (DevelopmentOnly))
	static void SetDebugLoggingEnabled(
	    UPARAM(meta = (Categories = "Debug"))
	    const FGameplayTag DebugTag,
	    const bool bEnabled
	)
	{
		const auto Config = TDTConfig::GetMutableOutputConfig();
		Config->UpdateOutputSettings(DebugTag, TDT_Undefined, static_cast<EDebugEnabled_TDT>(bEnabled), TDT_Undefined);
		
		if (const auto* FoundDelegates = DebugSettingsChangedEvents.Find(DebugTag))
		{
			FoundDelegates->Broadcast(Config->GetOutputSettings(DebugTag));
		}
	}
	
#pragma endregion Values Setters
	
#pragma endregion Values
	
#pragma region Delegates

	static TMap<FGameplayTag, FDebugOutputSettingsChangedMulticast> DebugSettingsChangedEvents;

	/**
	 * Binds a callback to changes in the debug message settings for the given tag.
	 *
	 * The callback is optionally invoked immediately with the current settings
	 * when the binding is established.
	 *
	 * @param DebugTag       Debug tag whose settings should be monitored.
	 * @param Callback       Callback to invoke when the settings change.
	 * @param bCallImmediately Whether to invoke the callback immediately after binding.
	 */
	UFUNCTION(BlueprintCallable, Category = "Toggleable Debug Tools|Messages|Delegates", meta = (DevelopmentOnly))
	static void BindToOutputSettingsChanged(
	    UPARAM(meta = (Categories = "Debug"))
	    const FGameplayTag DebugTag,
	    const FDebugOutputSettingsChangedCallback& Callback,
	    const bool bCallImmediately = true
	)
	{
	#if !(UE_BUILD_SHIPPING || UE_BUILD_TEST)
	    DebugSettingsChangedEvents.FindOrAdd(DebugTag).AddUnique(Callback);

	    if (bCallImmediately)
	    {
	    	if (const auto Config = UTDTConfigLibrary::GetMutableOutputConfig())
	    	{
	    		Callback.Execute(Config->GetOutputSettings(DebugTag));
	    	}
	    }
	#endif
	}

	/**
	 * Binds a callback to changes in the debug message settings for each tag
	 * in the given container.
	 *
	 * The callback is optionally invoked immediately with the current settings
	 * for each tag when the bindings are established.
	 *
	 * @param DebugTags        Debug tags whose settings should be monitored.
	 * @param Callback         Callback to invoke when the settings change.
	 * @param bCallImmediately Whether to invoke the callback immediately after binding.
	 */
	UFUNCTION(BlueprintCallable, Category = "Toggleable Debug Tools|Messages|Delegates", meta = (DevelopmentOnly))
	static void BindToAnyOutputSettingsChanged(
	    UPARAM(meta = (Categories = "Debug"))
	    const FGameplayTagContainer DebugTags,
	    const FDebugOutputSettingsChangedCallback& Callback,
	    const bool bCallImmediately = true
	)
	{
	#if !(UE_BUILD_SHIPPING || UE_BUILD_TEST)
	    for (const FGameplayTag& DebugTag : DebugTags)
	    {
	        DebugSettingsChangedEvents.FindOrAdd(DebugTag).AddUnique(Callback);

	        if (bCallImmediately)
	        {
	        	if (const auto Config = UTDTConfigLibrary::GetMutableOutputConfig())
	        	{
					Callback.Execute(Config->GetOutputSettings(DebugTag));
	        	}
	        }
	    }
	#endif
	}

	/**
	 * Removes a callback from all debug message settings change notifications.
	 */
	UFUNCTION(BlueprintCallable, Category = "Toggleable Debug Tools|Messages|Delegates", meta = (DevelopmentOnly))
	static void UnbindFromOutputSettingsChanged(
	    const FDebugOutputSettingsChangedCallback& Callback
	)
	{
	#if !(UE_BUILD_SHIPPING || UE_BUILD_TEST)
	    for (auto& Pair : DebugSettingsChangedEvents)
	    {
	        Pair.Value.Remove(Callback);
	    }
	#endif
	}
	
private:
	
	/**
	 * Broadcasts a debug message settings change to all callbacks bound to the given tag.
	 *
	 * Internal use only. This function should only be called by UTDTMessagesLibrary.
	 */
	static void BroadcastOutputSettingsChanged(
	    const FGameplayTag DebugTag,
	    const FDebugOutputSettings& Settings
	)
	{
	#if !(UE_BUILD_SHIPPING || UE_BUILD_TEST)
		if (const FDebugOutputSettingsChangedMulticast* Event =
			DebugSettingsChangedEvents.Find(DebugTag))
		{
			Event->Broadcast(Settings);
		}
	#endif
	}

public:
	
#pragma endregion Delegates
	
#pragma region Printing
	
	/**
	 * Conditionally prints a debug message to the screen and/or log based on the user's debug settings.
	 *
	 * The supplied debug tag is checked against the user's configured debug settings to determine
	 * whether the message should be displayed on screen, written to the log, or both.
	 *
	 * When logging is enabled, the message is written at the specified verbosity level. Messages
	 * logged at Verbose or lower visibility may not appear in the Output Log unless the corresponding
	 * log verbosity is enabled.
	 *
	 * @param Outer      Object used to provide world context and additional debug context.
	 * @param String     The message to display or log.
	 * @param Tag        Debug tag used to determine whether the message should be displayed or logged.
	 * @param Verbosity  Verbosity level used when writing the message to the log and determining its display style.
	 * @param Key        Optional key used to identify the on-screen message. Use NAME_None to display the message without a specific key.
	 */
	UFUNCTION(BlueprintCallable, 
		DisplayName = "Print String (Conditional)",
		Category = "Toggleable Debug Tools",
		meta = (
			Categories="Debug", 
			Keywords = "print print print print print print print string log conditional",
			DevelopmentOnly, 
			AdvancedDisplay = "2", 
			CallableWithoutWorldContext,
			WorldContext = "Outer",
			DefaultToSelf = "Outer", 
			HidePin = "Outer")
		)
	static void Print(
		const UObject* Outer, 
		const FString String = "Hello World!", 
		FGameplayTag Tag = FGameplayTag(), 
		const TDTVerbosityLevel Verbosity = TDTVerbosityLevel::Display, 
		const FName Key = NAME_None 
	);
		
	/** 
	 * Conditionally displays a debug message on screen and/or writes it to the log based on the user's debug settings. 
	 * 
	 * The supplied debug tag is checked against the user's configured debug settings to determine whether 
	 * the message should be displayed on screen, written to the log, or both. 
	 * 
	 * When logging is enabled, the message is written using the specified verbosity level. Messages logged 
	 * at Verbose or lower visibility may not appear in the Output Log unless the corresponding log verbosity 
	 * is enabled. 
	 * 
	 * @param Outer			Object used to provide world context and additional debug context. 
	 * @param Text			The text to display or log. 
	 * @param Tag			Debug tag used to determine whether the message should be displayed or logged. 
	 * @param Verbosity		Verbosity level used when writing the message to the log and determining its display style. 
	 * @param Key			Optional key used to identify the on-screen message. Use NAME_None to display the message without a specific key. 
	 */
	UFUNCTION(BlueprintCallable, 
		DisplayName = "Print Text (Conditional)", 
		Category = "Toggleable Debug Tools",
		meta = (
			Categories="Debug", 
			Keywords = "text print log conditional",
			DevelopmentOnly, 
			AdvancedDisplay = "2", 
			CallableWithoutWorldContext,
			WorldContext = "Outer",
			DefaultToSelf = "Outer", 
			HidePin = "Outer")
		)
	static void PrintText(
		const UObject* Outer, 
		const FText Text = INVTEXT("Hello World!"),
		const FGameplayTag Tag = FGameplayTag(), 
		const TDTVerbosityLevel Verbosity = TDTVerbosityLevel::Display, 
		const FName Key = NAME_None 
		)
	{
		Print(Outer, Text.ToString(), Tag, Verbosity, Key);
	}	
	
#pragma endregion Printing
	
#pragma region Logging
	
	/** 
	 * Conditionally writes a debug message to the log based on the user's debug settings. 
	 * 
	 * The supplied debug tag is checked against the user's configured debug settings to determine 
	 * whether the message should be written to the log. 
	 * 
	 * The message is written using the specified verbosity level. Depending on the configured log 
	 * verbosity, messages with lower visibility may not appear in the Output Log. 
	 * 
	 * @param Outer			Object used to provide world context and additional debug context. 
	 * @param String		The message to write to the log. 
	 * @param Tag			Debug tag used to determine whether the message should be logged. 
	 * @param Verbosity		Verbosity level used when writing the message to the log. 
	 */
	UFUNCTION(BlueprintCallable, 
		DisplayName = "Log String (Conditional)", 
		Category = "Toggleable Debug Tools",
		meta = (
			Categories="Debug", 
			Keywords = "string log conditional",
			DevelopmentOnly, 
			AdvancedDisplay = "2", 
			CallableWithoutWorldContext,
			WorldContext = "Outer",
			DefaultToSelf = "Outer", 
			HidePin = "Outer")
	)
	static void Log(
		const UObject* Outer, 
		const FString String = "Hello World!", 
		const FGameplayTag Tag = FGameplayTag(), 
		const TDTVerbosityLevel Verbosity = TDTVerbosityLevel::Display
		);
	
	/** 
	 * Conditionally writes a debug message to the log based on the user's debug settings. 
	 * 
	 * The supplied debug tag is checked against the user's configured debug settings to determine 
	 * whether the message should be written to the log. 
	 * 
	 * The message is written using the specified verbosity level. Depending on the configured log 
	 * verbosity, messages with lower visibility may not appear in the Output Log. 
	 * 
	 * @param Outer			Object used to provide world context and additional debug context. 
	 * @param Text			The message to write to the log. 
	 * @param Tag			Debug tag used to determine whether the message should be logged. 
	 * @param Verbosity		Verbosity level used when writing the message to the log. 
	 */
	UFUNCTION(BlueprintCallable, 
		DisplayName = "Log Text (Conditional)", 
		Category = "Toggleable Debug Tools",
		meta = (
			Categories="Debug", 
			Keywords = "text log conditional",
			DevelopmentOnly, 
			AdvancedDisplay = "2", 
			CallableWithoutWorldContext,
			WorldContext = "Outer",
			DefaultToSelf = "Outer", 
			HidePin = "Outer")
	)
	static void LogText(
		const UObject* Outer, 
		const FText Text = INVTEXT("Hello World!"), 
		const FGameplayTag Tag = FGameplayTag(), 
		const TDTVerbosityLevel Verbosity = TDTVerbosityLevel::Display
	)
	{
		Log(Outer, Text.ToString(), Tag, Verbosity);
	}

private:
	
	static void Internal_Log(const FString& String, const TDTVerbosityLevel Verbosity);

#pragma endregion Logging
	
	static void FormatTPSString(const UObject* Outer, FString& InString, const FGameplayTag& InTag, const TDTVerbosityLevel InVerbosity, const FName InKey);

};


using TDT = UTDTMessagesLibrary;
