// Copyright GCU 2026. All rights reserved.


#include "Interaction/Clickables/DraggableActor.h"

// Sets default values
ADraggableActor::ADraggableActor()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ADraggableActor::SetDragStrength(const FVector2D DragStrength)
{
	UE_LOG(LogTemp, Log, TEXT("  /  "));
	UE_LOG(LogTemp, Log, TEXT("  /  "));
	UE_LOG(LogTemp, Log, TEXT("Drag Strength Vector: X%f:Y%f"), DragStrength.X, DragStrength.Y);
	const float inputAngle = FMath::RadiansToDegrees(FMath::Atan2(DragStrength.Y, DragStrength.X));
	UE_LOG(LogTemp, Log, TEXT("Input angle: %f"), inputAngle);
	
	const float inputAngleOffsetFromTarget = FMath::FindDeltaAngleDegrees(inputAngle, TargetAngle);
	const float inputAngleProximity = FMath::Abs(inputAngleOffsetFromTarget);
	UE_LOG(LogTemp, Log, TEXT("Input angle proximity: %f"), inputAngleProximity);
	
	FVector2D output;
	
	if (UseTargetAngleToleranceFalloff)
	{
		// 20 = 42.5 - (45 / 2 = 22.5)
		float alpha = inputAngleProximity - TargetAngleTolerance / 2;
		UE_LOG(LogTemp, Log, TEXT("alpha 1: %f"), alpha);
		
		// 0.888... = 20 / (45 / 2 = 22.5) 
		alpha /= TargetAngleToleranceFalloff / 2;
		UE_LOG(LogTemp, Log, TEXT("alpha 2: %f"), alpha);
		
		output = DragStrength * FMath::Lerp(1.0f, 0.0f, FMath::Clamp(alpha, 0.0f, 1.0f));
		UE_LOG(LogTemp, Log, TEXT("alpha 3: %f"), FMath::Lerp(1.0f, 0.0f, FMath::Clamp(alpha, 0.0f, 1.0f)));
	}
	else
	{
		output = DragStrength * (inputAngleProximity < TargetAngleTolerance / 2);
	}
	
	UE_LOG(LogTemp, Log, TEXT("Pre-Clamp Output Vector: X%f:Y%f"), output.X, output.Y);
	UE_LOG(LogTemp, Log, TEXT("Pre-Clamp Output Length: X%f"), output.GetAbs().Length());
	
	// OutputVector = FVector2D::Min(output, output.GetSafeNormal());
	
	OutputVector = output.GetAbs().Length() < 1.0f ? output : output.GetSafeNormal();
	
	// OutputVector = FVector2D::Clamp(output, 
	// 	FVector2D(-1.0f), 
	// 	FVector2D(1.0f));
		
	OutputAlpha = OutputVector.Length();
	
	UE_LOG(LogTemp, Log, TEXT("!Output Vector: X%f:Y%f"), OutputVector.X, OutputVector.Y);
	UE_LOG(LogTemp, Log, TEXT("!Output Alpha: %f"), OutputAlpha);
}

void ADraggableActor::BeginPlay()
{
	TargetAngle = FMath::Wrap(TargetAngle - 90, -180.0f, 180.0f);

	Super::BeginPlay();
}

void ADraggableActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

