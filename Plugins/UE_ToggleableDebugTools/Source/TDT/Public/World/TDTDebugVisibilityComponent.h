// Copyright Kara Brown 2026. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Components/SceneComponent.h"
#include "TDTDebugVisibilityComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class TDT_API UDebugVisibilityComponent : public USceneComponent
{
	GENERATED_BODY()

public:

	UDebugVisibilityComponent();
	virtual void BeginPlay() override;
    
	/** Gameplay tag used to control whether this component's attached parent are displayed. */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Debug", meta=(Categories="Debug"))
	FGameplayTag DebugTag;
    
	/** Should control whether this component's attach parent is displayed. */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Debug")
	bool AffectsOwnerVisibility = true;
    
	/** Should control whether this component's actor parent is displayed. */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Debug")
	bool AffectsActorVisibility = false;

protected:
    
	/** Internally used to set visibility. */
	UFUNCTION()
	void OnDebugDrawingChanged(bool Enabled) const;

};
