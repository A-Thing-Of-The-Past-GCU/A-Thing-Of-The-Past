// Copyright Kara Brown 2026. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "TDTTypes.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Settings/TDTConfigLibrary.h"
#include "TDTWorldLibrary.generated.h"



DECLARE_DYNAMIC_DELEGATE_OneParam(FDebugDrawingEnabledChangedCallback, /*UObject*, Listener, */const bool, DebugDrawing);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDebugDrawingEnabledChangedMulticast, /*UObject*, Dispatcher, */const bool, DebugDrawing);


UCLASS()
class TDT_API UTDTDebugDrawingLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	
#pragma region Values	
	
#pragma region Values Getters

	/** */
	UFUNCTION(BlueprintCallable, Category = "Toggleable Debug Tools|World|Settings", meta = (DevelopmentOnly, ReturnDisplayName = "Out"))
	static bool IsDebugDrawingEnabled(UPARAM(meta = (Categories = "Debug")) const FGameplayTag DebugTag)
	{
#if !(UE_BUILD_SHIPPING || UE_BUILD_TEST)
		const auto OutputConfig = TDTConfig::GetMutableOutputConfig();
		if (!OutputConfig)
		{
			return false;
		}
		
		return OutputConfig->GetOutputSettings(DebugTag).DebugDrawingEnabled;
#else
		return false;
#endif
	}
	
#pragma endregion Values Getters
	
#pragma region Values Setters

	// /**
	//  * Sets the screen-printing and logging state for the given debug tag.
	//  *
	//  * @param DebugTag           Debug tag whose settings should be updated.
	//  * @param EnableScreenPrint  Whether messages should be printed to the screen.
	//  * @param EnableLogging      Whether messages should be written to the log.
	//  */
	// UFUNCTION(BlueprintCallable, Category = "Toggleable Debug Tools|World|Settings", meta = (DevelopmentOnly))
	// static void SetMessageSettings(
	//     UPARAM(meta = (Categories = "Debug"))
	//     const FGameplayTag DebugTag,
	//     bool EnableScreenPrint,
	//     bool EnableLogging
	// )
	// {
	// 	if (const auto Config = UTDTConfigLibrary::GetMutableOutputConfig())
	// 	{
	// 		Config->UpdateMessageOutputSettings(DebugTag, static_cast<EDebugEnabled_TDT>(EnableScreenPrint), static_cast<EDebugEnabled_TDT>(EnableLogging));
	// 		
	// 		if (const auto* FoundDelegates = DebugSettingsChangedEvents.Find(DebugTag))
	// 		{
	// 			FoundDelegates->Broadcast(GetMessageOutputSettings(DebugTag));
	// 		}
	// 	}
	// }

	/**	*/
	UFUNCTION(BlueprintCallable, Category = "Toggleable Debug Tools|World|Settings", meta = (DevelopmentOnly))
	static void SetDebugDrawingEnabled(
	    const FGameplayTag DebugTag,
	    const bool bEnabled
	)
	{
	#if !(UE_BUILD_SHIPPING || UE_BUILD_TEST)
		const auto OutputConfig = TDTConfig::GetMutableOutputConfig();
		
		OutputConfig->UpdateOutputSettings(DebugTag, TDT_Undefined, TDT_Undefined, static_cast<EDebugEnabled_TDT>(bEnabled));
		
		if (const auto* FoundDelegates = DebugDrawingEnabledChangedEvents.Find(DebugTag))
		{
			FoundDelegates->Broadcast(OutputConfig->GetOutputSettings(DebugTag).DebugDrawingEnabled);
		}
	#endif
	}
	
#pragma endregion Values Setters
	
#pragma endregion Values
	
#pragma region Delegates

	static TMap<FGameplayTag, FDebugDrawingEnabledChangedMulticast> DebugDrawingEnabledChangedEvents;

	/** */
	UFUNCTION(BlueprintCallable, Category = "Toggleable Debug Tools|World|Delegates", meta = (DevelopmentOnly))
	static void BindToDebugDrawingEnabledChanged(
	    UPARAM(meta = (Categories = "Debug"))
	    const FGameplayTag DebugTag,
	    const FDebugDrawingEnabledChangedCallback& Callback,
	    const bool bCallImmediately = true
	)
	{
	#if !(UE_BUILD_SHIPPING || UE_BUILD_TEST)
	    DebugDrawingEnabledChangedEvents.FindOrAdd(DebugTag).AddUnique(Callback);

	    if (bCallImmediately)
	    {
	        Callback.Execute(IsDebugDrawingEnabled(DebugTag));
	    }
	#endif
	}

	/** */
	UFUNCTION(BlueprintCallable, Category = "Toggleable Debug Tools|World|Delegates", meta = (DevelopmentOnly))
	static void BindToAnyDebugDrawingEnabledChanged(
	    UPARAM(meta = (Categories = "Debug"))
	    const FGameplayTagContainer DebugTags,
	    const FDebugDrawingEnabledChangedCallback& Callback,
	    const bool bCallImmediately = true
	)
	{
	#if !(UE_BUILD_SHIPPING || UE_BUILD_TEST)
	    for (const FGameplayTag& DebugTag : DebugTags)
	    {
	        DebugDrawingEnabledChangedEvents.FindOrAdd(DebugTag).AddUnique(Callback);

	        if (bCallImmediately)
	        {
	            Callback.Execute(IsDebugDrawingEnabled(DebugTag));
	        }
	    }
	#endif
	}

	/** */
	UFUNCTION(BlueprintCallable, Category = "Toggleable Debug Tools|World|Delegates", meta = (DevelopmentOnly))
	static void UnbindFromDebugDrawingEnabledChanged(
	    const FDebugDrawingEnabledChangedCallback& Callback
	)
	{
	#if !(UE_BUILD_SHIPPING || UE_BUILD_TEST)
	    for (auto& Pair : DebugDrawingEnabledChangedEvents)
	    {
	        Pair.Value.Remove(Callback);
	    }
	#endif
	}

	/**
	 * Broadcasts a debug message settings change to all callbacks bound to the given tag.
	 *
	 * Internal use only. This function should only be called by UTDTMessagesLibrary.
	 */
	static void BroadcastOutputSettingsChanged(
	    const FGameplayTag DebugTag,
	    const bool Settings
	)
	{
	#if !(UE_BUILD_SHIPPING || UE_BUILD_TEST)
		if (const FDebugDrawingEnabledChangedMulticast* Event =
			DebugDrawingEnabledChangedEvents.Find(DebugTag))
		{
			Event->Broadcast(Settings);
		}
	#endif
	}

#pragma endregion Delegates
	
#pragma region World

	// Sphere, Line, Box, Text etc.
	
#pragma endregion World
};


using TDTWorld = UTDTDebugDrawingLibrary;
