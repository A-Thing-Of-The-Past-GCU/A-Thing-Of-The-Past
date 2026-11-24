// Copyright Kara Brown 2026. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "TDTWorldLibrary.h"
#include "Kismet/BlueprintAsyncActionBase.h"
// #include "Messages/TDTMessagesLibrary.h"
#include "OnDebugDrawingEnabledChanged.generated.h"


UCLASS()
class TDT_API UOnDebugDrawingEnabledChanged : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

private:
	
	FGameplayTagContainer DebugTags;
	bool bImmediateCallback = true;

	FDebugDrawingEnabledChangedCallback NativeCallback;

public:

	/** */
	UPROPERTY(BlueprintAssignable) FDebugDrawingEnabledChangedMulticast OnChanged;
	
	/** */
	UFUNCTION(BlueprintCallable, 
		Category = "Toggleable Debug Tools|World|Delegates",
		meta = (
			BlueprintInternalUseOnly = "true",
			DisplayName = "On Debug Draw Enabled Changed"))
	static UOnDebugDrawingEnabledChanged* OnDebugDrawEnabledChanged( UPARAM(meta = (Categories = "Debug")) const FGameplayTag Tag, const bool CallImmediately = true)
	{
		UOnDebugDrawingEnabledChanged* Node = NewObject<UOnDebugDrawingEnabledChanged>();

		Node->DebugTags = FGameplayTagContainer(Tag);
		Node->bImmediateCallback = CallImmediately;

		return Node;
	}
	
	
	/** */
	UFUNCTION(BlueprintCallable, 
		Category = "Toggleable Debug Tools|World|Delegates",
		meta = (
			BlueprintInternalUseOnly = "true",
			DisplayName = "On Debug Draw Enabled Changed (Multiple)"))
	static UOnDebugDrawingEnabledChanged* OnAnyDebugDrawEnabledChanged( UPARAM(meta = (Categories = "Debug")) const FGameplayTagContainer Tags, const bool CallImmediately = true)
	{
		UOnDebugDrawingEnabledChanged* Node = NewObject<UOnDebugDrawingEnabledChanged>();
	
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
			TDTWorld::BindToDebugDrawingEnabledChanged(DebugTag, NativeCallback, bImmediateCallback);		
			bImmediateCallback = false;
		}
#endif
	}

private:

	UFUNCTION() void HandleDebugChanged(const bool bEnabled) const
	{
		OnChanged.Broadcast(bEnabled);
	}
};
