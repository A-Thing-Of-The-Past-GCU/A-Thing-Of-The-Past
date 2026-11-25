// Copyright GCU 2026. All rights reserved.


#include "Interaction/Clickables/DraggableComponent.h"

#include "Blueprint/WidgetLayoutLibrary.h"

// Sets default values
UDraggableComponent::UDraggableComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	PrimaryComponentTick.bStartWithTickEnabled = true;
}

UDraggableComponent::~UDraggableComponent()
{
	if (InteractionTarget)
	{
		InteractionTarget->OnClicked.RemoveDynamic(this, &UDraggableComponent::OnTargetClicked);
		InteractionTarget->OnReleased.RemoveDynamic(this, &UDraggableComponent::OnTargetReleased);
		
		InteractionTarget->DestroyComponent();
		InteractionTarget = nullptr;
	}
	
	if (InteractionWidget)
	{
		InteractionWidget->DestroyComponent();
		InteractionWidget = nullptr;
	}
	
	if (InteractionPromptWidget)
	{
		InteractionPromptWidget->DestroyComponent();
		InteractionPromptWidget = nullptr;
	}
}

void UDraggableComponent::SetInteractionEnabled()
{
	if (Enabled)
	{
		return;
	}
	
	TargetClickedCursorLocation = UWidgetLayoutLibrary::GetMousePositionOnViewport(this);
	InteractionPromptWidget->SetVisibility(false);
	InteractionWidget->SetVisibility(true);
	Enabled = true;
	
	onDragComponentStarted.Broadcast();
	
	InteractionTarget->SetSphereRadius(10000.0f);
}

void UDraggableComponent::SetInteractionDisabled()
{
	if (!Enabled)
	{
		return;
	}
	
	TargetClickedCursorLocation = FVector2D::ZeroVector;
	
	DisableInteractionWidget();
	
	SetDragStrength(TargetClickedCursorLocation);
	Enabled = false;
	
	onDragComponentEnded.Broadcast();
	
	InteractionTarget->SetSphereRadius(SphereRadius);
}

void UDraggableComponent::DisableInteractionWidget()
{
	InteractionPromptWidget->SetVisibility(true);
	InteractionWidget->SetVisibility(false);
}

void UDraggableComponent::SetPromptHiddenInGame(const bool bHidden)
{
	InteractionPromptWidget->SetHiddenInGame(bHidden);
}

void UDraggableComponent::OnRegister()
{
	Super::OnRegister();
	
	if (!InteractionTarget)
	{
		InteractionTarget = NewObject<USphereComponent>(this, TEXT("Interaction Target"));
		InteractionTarget->AttachToComponent(this, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
		
		InteractionTarget->RegisterComponent();
	}
	
	InteractionTarget->SetSphereRadius(SphereRadius);
	InteractionTarget->SetCollisionProfileName("UI");
		
	InteractionTarget->OnClicked.AddUniqueDynamic(this, &UDraggableComponent::OnTargetClicked);
	InteractionTarget->OnReleased.AddUniqueDynamic(this, &UDraggableComponent::OnTargetReleased);
	
	if (!InteractionWidget)
	{
		InteractionWidget = NewObject<UWidgetComponent>(this, TEXT("Interaction Widget"));
		InteractionWidget->AttachToComponent(this, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
		
		InteractionWidget->RegisterComponent();
	}
	
	InteractionWidget->SetWidgetClass(InteractionWidgetClass);
		
	InteractionWidget->SetCollisionProfileName("NoCollision");
	InteractionWidget->SetVisibility(false);
	InteractionWidget->SetWidgetSpace(EWidgetSpace::Screen);
	InteractionWidget->SetDrawAtDesiredSize(false);
	InteractionWidget->SetPivot(FVector2D(0.0f, 0.0f));
	
	InteractionWidget->SetRelativeLocationAndRotation(InteractionWidgetTransform.GetLocation(), InteractionWidgetTransform.GetRotation());
	InteractionWidget->SetWorldScale3D(InteractionWidgetTransform.GetScale3D());
	
	if (!InteractionPromptWidget)
	{
		InteractionPromptWidget = NewObject<UWidgetComponent>(this, TEXT("Interaction Telegraph Widget"));
		InteractionPromptWidget->AttachToComponent(this, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
		
		InteractionPromptWidget->RegisterComponent();
	}
		
	InteractionPromptWidget->SetWidgetClass(InteractionPromptWidgetClass);
	
	if (InteractionPromptWidget)
	{
		InteractionPromptWidget->SetMaterial(0, InteractionPromptMaterial);
	}
		
	InteractionPromptWidget->SetCollisionProfileName("NoCollision");
	InteractionPromptWidget->SetVisibility(true);
	InteractionPromptWidget->SetWidgetSpace(EWidgetSpace::World);
	InteractionPromptWidget->SetDrawAtDesiredSize(true);
	
	InteractionPromptWidget->SetRelativeLocationAndRotation(PromptWidgetTransform.GetLocation(), PromptWidgetTransform.GetRotation());
	InteractionPromptWidget->SetWorldScale3D(PromptWidgetTransform.GetScale3D());
	// InteractionPromptWidget->SetRelativeTransform(PromptWidgetTransform);
	
	
}

void UDraggableComponent::OnUnregister()
{
	Super::OnUnregister();
	
	if (InteractionTarget)
	{
		InteractionTarget->OnClicked.RemoveDynamic(this, &UDraggableComponent::OnTargetClicked);
		InteractionTarget->OnReleased.RemoveDynamic(this, &UDraggableComponent::OnTargetReleased);
		
		InteractionTarget->DestroyComponent();
		InteractionTarget = nullptr;
	}
	
	if (InteractionWidget)
	{
		InteractionWidget->DestroyComponent();
		InteractionWidget = nullptr;
	}
	
	if (InteractionPromptWidget)
	{
		InteractionPromptWidget->DestroyComponent();
		InteractionPromptWidget = nullptr;
	}
	
}

void UDraggableComponent::OnTargetClicked(UPrimitiveComponent* TouchedComponent, FKey ButtonPressed)
{
	SetInteractionEnabled();
}

void UDraggableComponent::OnTargetReleased(UPrimitiveComponent* TouchedComponent, FKey ButtonReleased)
{
	SetInteractionDisabled();
} 

void UDraggableComponent::SetDragStrength(const FVector2D DragStrength)
{
	const FVector2D ScaledDragStrength = DragStrength / MaxDragDistance;
	//UE_LOG(LogTemp, Log, TEXT("  /  "));
	//UE_LOG(LogTemp, Log, TEXT("  /  "));
	//UE_LOG(LogTemp, Log, TEXT("Drag Strength Vector: X%f:Y%f"), ScaledDragStrength.X, ScaledDragStrength.Y);
	const float inputAngle = FMath::RadiansToDegrees(FMath::Atan2(ScaledDragStrength.Y, ScaledDragStrength.X));
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
		
		output = ScaledDragStrength * FMath::Lerp(1.0f, 0.0f, FMath::Clamp(alpha, 0.0f, 1.0f));
		//UE_LOG(LogTemp, Log, TEXT("alpha 3: %f"), FMath::Lerp(1.0f, 0.0f, FMath::Clamp(alpha, 0.0f, 1.0f)));
	}
	else
	{
		output = ScaledDragStrength * (inputAngleProximity < TargetAngleTolerance / 2);
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
		//UE_LOG(LogTemp, Log, TEXT("OutputStrength Offset: %f"), hold);
		
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
	
	InteractionWidget->InitWidget();
	InteractionPromptWidget->InitWidget();
	
	if (InteractionWidget->GetUserWidgetObject())
	{
		if (UDraggableWidget* draggableWidget = Cast<UDraggableWidget>(InteractionWidget->GetWidget()))
		{
			draggableWidget->DraggableComponent = this;
		}
	}
	else
	{
		UE_LOG(LogEngine, Error, TEXT("BadWidget"))
	}
	
	if (InteractionPromptWidget->GetUserWidgetObject())
	{
		if (UCursorInteractionPromptWidget* interactionPromptWidget = Cast<UCursorInteractionPromptWidget>(InteractionPromptWidget->GetWidget()))
		{
			interactionPromptWidget->AssignOverlapPrimitive(InteractionTarget);
		}
	}
}

void UDraggableComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	if (Enabled)
	{
		SetDragStrength(UWidgetLayoutLibrary::GetMousePositionOnViewport(this) -  TargetClickedCursorLocation);
	}
}

void UDraggableComponent::Activate(bool bReset)
{
	Super::Activate(bReset);
	
	InteractionTarget->Activate(bReset);
	InteractionWidget->Activate(bReset);
	InteractionPromptWidget->Activate(bReset);
}

void UDraggableComponent::Deactivate()
{
	Super::Deactivate();
	
	InteractionTarget->Deactivate();
	InteractionWidget->Deactivate();
	InteractionPromptWidget->Deactivate();
}
