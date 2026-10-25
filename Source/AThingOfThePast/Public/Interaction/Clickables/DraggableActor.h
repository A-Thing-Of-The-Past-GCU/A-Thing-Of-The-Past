// Copyright GCU 2026. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DraggableActor.generated.h"

UCLASS()
class ATHINGOFTHEPAST_API ADraggableActor : public AActor
{
	GENERATED_BODY()
	
public:	
	ADraggableActor();
	
	UFUNCTION(BlueprintCallable)
	void SetDragStrength(const FVector2D DragStrength);
	
	/** Desired drag angle (0 = 12:00. 90 = 03:) */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Configuration, meta = (UIMin = -180, UIMax = 180))
	float TargetAngle = 45.0f;
	
	/** Safe area around the target drag angle that still rewards maximum strength. */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Configuration, meta = (UIMin = 0, UIMax = 360))
	float TargetAngleTolerance = 45.0f;
	
	UPROPERTY()
	bool UseTargetAngleToleranceFalloff = true;
	
	/** Additional soft falloff angle after leaving the Target Angle, and the Target Angle Tolerance. */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Configuration, meta = (UIMin = 0, UIMax = 180, EditCondition = UseTargetAngleToleranceFalloff))
	float TargetAngleToleranceFalloff = 45.0f;
	
	/** The desired strength of the interaction between 0, and 1. */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Configuration, meta = (UIMin = 0, UIMax = 1))
	float TargetStrength = 0.5;
	
	/** Safe area around the target strength that still rewards maximum strength*/
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Configuration, meta = (UIMin = 0, UIMax = 1))
	float TargetStrengthTolerance = 0.25;
	
	UPROPERTY()
	bool UseTargetStrengthToleranceFalloff = true;
	
	/** Additional soft falloff angle after leaving the Target Strength, and the Target Strength Tolerance. */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Configuration, meta = (UIMin = 0, UIMax = 180, EditCondition = UseTargetStrengthToleranceFalloff))
	float TargetStrengthToleranceFalloff = 45.0f;
	
	//Player input after being processed.
	UPROPERTY(BlueprintReadOnly, Category = Output)
	FVector2D OutputVector;
	
	//Player input after being processed and measured.
	UPROPERTY(BlueprintReadOnly, Category = Output)
	float OutputAlpha;

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;
};
