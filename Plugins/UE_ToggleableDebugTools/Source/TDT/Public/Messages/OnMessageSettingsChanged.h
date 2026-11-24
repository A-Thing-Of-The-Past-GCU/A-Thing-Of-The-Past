// Copyright Kara Brown 2026. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "Messages/TDTMessagesLibrary.h"
#include "OnMessageSettingsChanged.generated.h"


UCLASS()
class TDT_API UOnMessageSettingsChanged : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:

	/** Called whenever the given debug tag is changed and conditionally when binding is made*/
	UPROPERTY(BlueprintAssignable) FDebugOutputSettingsChangedMulticast OnChanged;

	
	/** OnChanged is called whenever the given debug tag is changed and conditionally when binding is made
	 * 
	 * @param Tag				The debug tag that OnChanged is bound to
	 * @param CallImmediately	Whether OnChanged be called immediately
	 */
	UFUNCTION(BlueprintCallable, 
		Category = "Toggleable Debug Tools|Messages|Delegates",
		meta = (
			BlueprintInternalUseOnly = "true",
			DisplayName = "On Message Settings Changed"))
	static UOnMessageSettingsChanged* OnMessageSettingsChanged( UPARAM(meta = (Categories = "Debug")) const FGameplayTag Tag, const bool CallImmediately = true)
	{
		UOnMessageSettingsChanged* Node = NewObject<UOnMessageSettingsChanged>();

		Node->DebugTags = FGameplayTagContainer(Tag);
		Node->bImmediateCallback = CallImmediately;

		return Node;
	}
	
	
	/** OnChanged is called whenever one of the given debug tags are changed and conditionally when binding is made
	 * 
	 * @param Tags				The debug tags that OnChanged is bound to
	 * @param CallImmediately	Whether OnChanged be called immediately
	 */
	UFUNCTION(BlueprintCallable, 
		Category = "Toggleable Debug Tools|Messages|Delegates",
		meta = (
			BlueprintInternalUseOnly = "true",	
			DisplayName = "On Message Settings Changed (Multiple)"))
	static UOnMessageSettingsChanged* OnAnyMessageSettingsChanged( UPARAM(meta = (Categories = "Debug")) const FGameplayTagContainer Tags, const bool CallImmediately = true)
	{
		UOnMessageSettingsChanged* Node = NewObject<UOnMessageSettingsChanged>();
	
		Node->DebugTags = Tags;
		Node->bImmediateCallback = CallImmediately;
	
		return Node;
	}

	virtual void Activate() override
	{
#if !(UE_BUILD_SHIPPING || UE_BUILD_TEST)
	
		NativeCallback.BindUFunction(this, FName("HandleDebugChanged"));

		for (const auto DebugTag : DebugTags)
		{
			TDT::BindToOutputSettingsChanged(DebugTag, NativeCallback, bImmediateCallback);		
			bImmediateCallback = false;
		}
#endif
	}
// 	virtual void BeginDestroy() override
// 	{
// #if !(UE_BUILD_SHIPPING || UE_BUILD_TEST)
// 		TDT::UnbindFromMessageSettingsChanged(NativeCallback);
// #endif
// 		Super::BeginDestroy();
// 	}

private:

	UFUNCTION() void HandleDebugChanged(const FDebugOutputSettings& newValues) const
	{
		OnChanged.Broadcast(newValues);
	}
	
	FGameplayTagContainer DebugTags;
	bool bImmediateCallback = true;

	FDebugOutputSettingsChangedCallback NativeCallback;
};
