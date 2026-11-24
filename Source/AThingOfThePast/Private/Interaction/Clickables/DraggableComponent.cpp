// Copyright GCU 2026. All rights reserved.


#include "Interaction/Clickables/DraggableComponent.h"

#include "Blueprint/WidgetLayoutLibrary.h"

// Sets default values
UDraggableComponent::UDraggableComponent()
{
}

void UDraggableComponent::OnRegister()
{
	Super::OnRegister();
	
	if (!InteractionTarget)
	{
		InteractionTarget = NewObject<USphereComponent>(this, TEXT("Interaction Target"));
		InteractionTarget->AttachToComponent(this, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
		InteractionTarget->RegisterComponent();
	
		InteractionTarget->SetSphereRadius(SphereRadius);
		
		InteractionTarget->OnClicked.AddUniqueDynamic(this, &UDraggableComponent::OnTargetClicked);
		InteractionTarget->OnReleased.AddUniqueDynamic(this, &UDraggableComponent::OnTargetReleased);
	}
	
	if (!InteractionWidget)
	{
		InteractionWidget = NewObject<UWidgetComponent>(this, TEXT("Interaction Widget"));
		InteractionWidget->AttachToComponent(this, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
		InteractionWidget->RegisterComponent();
		
		InteractionWidget->SetVisibility(false);
		
		InteractionWidget->SetWidgetSpace(EWidgetSpace::Screen);
		InteractionWidget->SetDrawAtDesiredSize(true);
	}
	
	if (!InteractionTelegraphWidget)
	{
		InteractionTelegraphWidget = NewObject<UWidgetComponent>(this, TEXT("Interaction Telegraph Widget"));
		InteractionTelegraphWidget->AttachToComponent(this, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
		InteractionTelegraphWidget->RegisterComponent();
		
		InteractionTelegraphWidget->SetVisibility(true);
		
		InteractionWidget->SetWidgetSpace(EWidgetSpace::Screen);
		InteractionTelegraphWidget->SetDrawAtDesiredSize(true);
	}
	
}

void UDraggableComponent::OnUnregister()
{
	Super::OnUnregister();
	
	if (InteractionTarget)
	{
		InteractionTarget->OnClicked.RemoveDynamic(this, &UDraggableComponent::OnTargetClicked);
		
		InteractionTarget->DestroyComponent();
		InteractionTarget = nullptr;
	}
	
	if (InteractionWidget)
	{
		InteractionWidget->DestroyComponent();
		InteractionWidget = nullptr;
	}
	
	if (InteractionTelegraphWidget)
	{
		InteractionTelegraphWidget->DestroyComponent();
		InteractionTelegraphWidget = nullptr;
	}
	
}

void UDraggableComponent::OnTargetClicked(UPrimitiveComponent* TouchedComponent, FKey ButtonPressed)
{
	TargetClickedCursorLocation = UWidgetLayoutLibrary::GetMousePositionOnViewport(this);
	InteractionTelegraphWidget->SetVisibility(false);
	InteractionWidget->SetVisibility(true);
	Enabled = true;
	
	InteractionTarget->SetSphereRadius(10000.0f);
}

void UDraggableComponent::OnTargetReleased(UPrimitiveComponent* TouchedComponent, FKey ButtonReleased)
{
	TargetClickedCursorLocation = FVector2D::ZeroVector;
	InteractionTelegraphWidget->SetVisibility(true);
	InteractionWidget->SetVisibility(false);
	SetDragStrength(TargetClickedCursorLocation);
	Enabled = false;
	
	InteractionTarget->SetSphereRadius(SphereRadius);
} 

void UDraggableComponent::SetDragStrength(const FVector2D DragStrength)
{
	//UE_LOG(LogTemp, Log, TEXT("  /  "));
	//UE_LOG(LogTemp, Log, TEXT("  /  "));
	//UE_LOG(LogTemp, Log, TEXT("Drag Strength Vector: X%f:Y%f"), DragStrength.X, DragStrength.Y);
	const float inputAngle = FMath::RadiansToDegrees(FMath::Atan2(DragStrength.Y, DragStrength.X));
	//UE_LOG(LogTemp, Log, TEXT("Input angle: %f"), inputAngle);
	
	const float inputAngleOffsetFromTarget = FMath::FindDeltaAngleDegrees(inputAngle, TargetAngle);
	const float inputAngleProximity = FMath::Abs(inputAngleOffsetFromTarget);
	//UE_LOG(LogTemp, Log, TEXT("Input angle proximity: %f"), inputAngleProximity);
	
	FVector2D output;
	
	if (UseTargetAngleToleranceFalloff)
	{
		// 20 = 42.5 - (45 / 2 = 22.5)
		float alpha = inputAngleProximity - TargetAngleTolerance / 2;
		//UE_LOG(LogTemp, Log, TEXT("alpha 1: %f"), alpha);
		
		// 0.888... = 20 / (45 / 2 = 22.5) 
		alpha /= TargetAngleToleranceFalloff / 2;
		//UE_LOG(LogTemp, Log, TEXT("alpha 2: %f"), alpha);
		
		output = DragStrength * FMath::Lerp(1.0f, 0.0f, FMath::Clamp(alpha, 0.0f, 1.0f));
		//UE_LOG(LogTemp, Log, TEXT("alpha 3: %f"), FMath::Lerp(1.0f, 0.0f, FMath::Clamp(alpha, 0.0f, 1.0f)));
	}
	else
	{
		output = DragStrength * (inputAngleProximity < TargetAngleTolerance / 2);
	}
	
	//UE_LOG(LogTemp, Log, TEXT("Pre-Clamp Output Vector: X%f:Y%f"), output.X, output.Y);
	//UE_LOG(LogTemp, Log, TEXT("Pre-Clamp Output Length: %f"), output.GetAbs().Length());
	
	OutputVector = output.GetAbs().Length() < 1.0f ? output : output.GetSafeNormal();
	
	float OutputLength = OutputVector.Length();
	//UE_LOG(LogTemp, Log, TEXT("Output Length: %f"), OutputLength);
	
	float OutputStrengthOffset = FMath::Abs(OutputLength - TargetStrength);
	//UE_LOG(LogTemp, Log, TEXT("Output Strength Offset: %f"), OutputStrengthOffset);
	
	if (UseTargetStrengthToleranceFalloff)
	{
		float hold = (OutputStrengthOffset - TargetStrengthTolerance / 2) / TargetStrengthToleranceFalloff;
		OutputAlpha = FMath::Lerp(AlphaMax, AlphaMin, FMath::Clamp(hold, 0.0f, 1.0f));	
	}
	else
	{
		OutputAlpha = (OutputStrengthOffset <= TargetStrength + TargetStrengthTolerance / 2) ? AlphaMax : AlphaMin;
	}
	
	
	
	
	//UE_LOG(LogTemp, Log, TEXT("!Output Vector: X%f:Y%f"), OutputVector.X, OutputVector.Y);
	//UE_LOG(LogTemp, Log, TEXT("!Output Alpha: %f"), OutputAlpha);
}

void UDraggableComponent::BeginPlay()
{
	TargetAngle = FMath::Wrap(TargetAngle - 90, -180.0f, 180.0f);

	Super::BeginPlay();
}

void UDraggableComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	if (Enabled)
	{
		SetDragStrength(UWidgetLayoutLibrary::GetMousePositionOnViewport(this) -  TargetClickedCursorLocation);
	}
}
