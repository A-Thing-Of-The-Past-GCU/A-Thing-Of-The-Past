// Copyright Kara Brown 2026. All Rights Reserved.


#include "World/TDTDebugVisibilityComponent.h"

#include "World/TDTWorldLibrary.h"

UDebugVisibilityComponent::UDebugVisibilityComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UDebugVisibilityComponent::BeginPlay()
{
	Super::BeginPlay();

#if !(UE_BUILD_SHIPPING || UE_BUILD_TEST)
	
	FDebugDrawingEnabledChangedCallback Callback;
	Callback.BindUFunction(this, FName("OnDebugDrawingChanged"));
	
	TDTWorld::BindToDebugDrawingEnabledChanged(DebugTag, Callback, true);
	
#endif
}

void UDebugVisibilityComponent::OnDebugDrawingChanged(const bool Enabled) const
{
	if (AffectsOwnerVisibility)
	{
		if (const auto _attachParent = GetAttachParent())
		{
			_attachParent->SetHiddenInGame(!Enabled);
		}
	}
	if (AffectsActorVisibility)
	{
		GetOwner()->SetActorHiddenInGame(!Enabled);
	}
}

