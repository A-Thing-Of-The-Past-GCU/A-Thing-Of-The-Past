// Copyright Kara Brown 2026. All Rights Reserved.


#include "World/Volume/TDTDebugVolumeVisualizerComponent.h"

#include "TDTTypes.h"
#include "CoreMinimal.h"
#include "Engine/StaticMesh.h"
#include "World/TDTWorldLibrary.h"
#include "Components/BoxComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/SphereComponent.h"
#include "Components/CapsuleComponent.h"
#include "Messages/TDTMessagesLibrary.h"
#include "Components/StaticMeshComponent.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "World/Widget/TDTDebugWidgetComponent.h"

UDebugVolumeVisualizerComponent::UDebugVolumeVisualizerComponent()
{
	SetCastShadow(false);
	SetHiddenInGame(true);
	
#if !(UE_BUILD_SHIPPING || UE_BUILD_TEST)
	
	{
		static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshFinder(
			TEXT("/Engine/BasicShapes/Cube.Cube"));
	
		if (MeshFinder.Succeeded())
		{
			BoxPreviewMesh = MeshFinder.Object;
		}
		else
		{
			PRINT(TAG_DEBUG_TDT, TDT_Fatal, "Unabled to find mesh at '/Engine/BasicShapes/Cube.Cube', will be unabled to construct visualizations.");
		}
	}
	
	{
		static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshFinder(
		TEXT("/TDT/Assets/Hemisphere.Hemisphere"));
			
		if (MeshFinder.Succeeded())
		{
			HemispherePreviewMesh = MeshFinder.Object;
		}
		else
		{
			PRINT(TAG_DEBUG_TDT, TDT_Fatal, "Unabled to find mesh at '/TDT/Hemisphere.Hemisphere', will be unabled to construct visualizations.");
		}
	}
		
	{
		static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshFinder(
		TEXT("/TDT/Assets/Cylinder.Cylinder"));
			
		if (MeshFinder.Succeeded())
		{
			CylinderPreviewMesh = MeshFinder.Object;
		}
		else
		{
			PRINT(TAG_DEBUG_TDT, TDT_Fatal, "Unabled to find mesh at '/TDT/Cylinder.Cylinder', will be unabled to construct visualizations.");
		}
	}
	
	static ConstructorHelpers::FObjectFinder<UMaterialInterface> MaterialFinder(
		TEXT("/TDT/Assets/MI_DebugRadiusPreview.MI_DebugRadiusPreview")
	);

	if (MaterialFinder.Succeeded())
	{
		PreviewMaterial = MaterialFinder.Object;
	}
	
	DebugTag = TAG_DEBUG_World;
	
#endif
}

void UDebugVolumeVisualizerComponent::SetDebugText(const FText InText)
{
	if (!DebugWidgetComponent) return;
	DebugWidgetComponent->SetDebugText(InText);
}

void UDebugVolumeVisualizerComponent::BeginPlay()
{
	Super::BeginPlay();
	
#if !(UE_BUILD_SHIPPING || UE_BUILD_TEST)
	
	FDebugDrawingEnabledChangedCallback Callback;
	Callback.BindUFunction(this, FName("OnDebugDrawingChanged"));
	
	TDTWorld::BindToDebugDrawingEnabledChanged(DebugTag, Callback, true);
	
#endif
}

void UDebugVolumeVisualizerComponent::UpdatePreview()
{
	
#if !(UE_BUILD_SHIPPING || UE_BUILD_TEST)

	if (ParentShapeComponent.IsA(UBoxComponent::StaticClass()))
	{
		PRINT(TAG_DEBUG_TDT, TDT_VeryVerbose, "Parent Component is of type UBoxComponent, Calling their update preview.");
		UpdateBoxPreview();
	}
	else if (ParentShapeComponent.IsA(USphereComponent::StaticClass()))
	{
		PRINT(TAG_DEBUG_TDT, TDT_VeryVerbose, "Parent Component is of type USphereComponent, Calling their update preview.");
		UpdateSpherePreview();
	}
	else if (ParentShapeComponent.IsA(UCapsuleComponent::StaticClass()))
	{
		PRINT(TAG_DEBUG_TDT, TDT_VeryVerbose, "Parent Component is of type UCapsuleComponent, Calling their update preview.");
		UpdateCapsulePreview();
	}
	
#endif

}

#if !(UE_BUILD_SHIPPING || UE_BUILD_TEST)



void UDebugVolumeVisualizerComponent::OnRegister()
{
	Super::OnRegister();
	
	SetCollisionEnabled(ECollisionEnabled::NoCollision);
	
	if (!GetWorld())
		return;

	USceneComponent* attachParent = GetAttachParent();
	
	if (!attachParent)
		return;
	
	ParentShapeComponent = Cast<UShapeComponent>(attachParent);
	
	if (!ParentShapeComponent)
	{
		PRINT(TAG_DEBUG_TDT, TDT_Warning, "Parent of Visualiser is of type %s, not UShapeComponent. Visualisation will not appear.", *attachParent->StaticClass()->GetName());
		return;
	}

	DynamicMaterial = UMaterialInstanceDynamic::Create(
		PreviewMaterial,
		this
	);

	if (DynamicMaterial)
	{
		UpdatePreviewColor(Preview_Color);
		
		// DynamicMaterial->SetScalarParameterValue(FName("AlphaMax"), 0.8f);
		// DynamicMaterial->SetScalarParameterValue(FName("AlphaMin"), 0.02f);
		// DynamicMaterial->SetScalarParameterValue(FName("PulseLevel"), 1.25f);

		SetMaterial(
			0,
			DynamicMaterial
		);
	}
	
	UpdatePreview();
	EnsureDebugWidgetComponent();
}

void UDebugVolumeVisualizerComponent::OnUnregister()
{
	if (DebugWidgetComponent)
	{
		DebugWidgetComponent->DestroyComponent();
		DebugWidgetComponent = nullptr;
	}

	for (int i = DebugHemisphereComponents.Num() - 1; i >= 0; --i)
	{
		if (const auto Comp = DebugHemisphereComponents[i])
		{
			Comp->DestroyComponent();
		}
	}
    
	Super::OnUnregister();
}

void UDebugVolumeVisualizerComponent::EnsureDebugHemisphereComponents()
{
	EnsureDestroyDebugHemisphereComponents();
	
	DebugHemisphereComponents.Empty();
	
	for (int i = 0; i < 2; ++i)
	{
		auto* HemisphereComponent =
			NewObject<UStaticMeshComponent>(this, FName("DebugHemisphere", i));

		if (!HemisphereComponent)
		{
			PRINT(TAG_DEBUG_TDT, TDT_Fatal, "UNABLE TO INSTANTIATE NEW STATIC MESH COMPONENT AT INDEX %d", i);
			return;
		}
		
		HemisphereComponent->SetStaticMesh(HemispherePreviewMesh);
		HemisphereComponent->SetMaterial(0, DynamicMaterial);

		HemisphereComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		HemisphereComponent->SetCastShadow(false);
		HemisphereComponent->SetHiddenInGame(true);

		HemisphereComponent->AttachToComponent(
			GetAttachParent(),
			FAttachmentTransformRules::SnapToTargetNotIncludingScale
		);

		HemisphereComponent->RegisterComponent();

		DebugHemisphereComponents.Add(HemisphereComponent);
	}
}

void UDebugVolumeVisualizerComponent::EnsureDestroyDebugHemisphereComponents()
{
	for (int i = DebugHemisphereComponents.Num() - 1; i >= 0; --i)
	{
		if (const auto Comp = DebugHemisphereComponents[i])
		{
			Comp->DestroyComponent();
		}
	}
}

void UDebugVolumeVisualizerComponent::EnsureDebugWidgetComponent()
{
	if (EnableDebugWidget)
	{
		if (!DebugWidgetComponent)
		{
			DebugWidgetComponent = NewObject<UDebugTextWidgetComponent>(this, TEXT("DebugWidgetInternal"));
        
			if (DebugWidgetComponent)
			{
				DebugWidgetComponent->AttachToComponent(this, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
				
				DebugWidgetComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
				DebugWidgetComponent->SetHiddenInGame(true);
				DebugWidgetComponent->SetCastShadow(false);
				
				DebugWidgetComponent->RegisterComponent();
			}
		}
		
		DebugWidgetComponent->DebugTag = DebugTag;
		DebugWidgetComponent->DefaultText = DefaultText;
		
	}
	else
	{
		EnsureDestroyDebugWidgetComponent();
	}
}

void UDebugVolumeVisualizerComponent::EnsureDestroyDebugWidgetComponent()
{
	if (DebugWidgetComponent)
	{
		DebugWidgetComponent->DestroyComponent();
		DebugWidgetComponent = nullptr;
	}
}

void UDebugVolumeVisualizerComponent::UpdateBoxPreview()
{
	if (!DynamicMaterial)
	{
		PRINT(TAG_DEBUG_TDT, TDT_Warning, "UpdateBoxPreview: Invalid DynamicMaterial, leaving early and unchanged.");
		return;
	}
	
	const UBoxComponent* component = Cast<UBoxComponent>(ParentShapeComponent);
	if (!component)
	{
		PRINT(TAG_DEBUG_TDT, TDT_Warning, "UpdateBoxPreview: ParentShapeComponent is not of type UBoxComponent (is instead %s), leaving early and unchanged.", *ParentShapeComponent.GetClass()->GetName());
		return;
	}
	
	EnsureDestroyDebugHemisphereComponents();
	
	SetStaticMesh(BoxPreviewMesh);
	SetMaterial(0, DynamicMaterial);
	
	SetRelativeLocation(FVector(0.0f));
	SetRelativeScale3D(component->GetUnscaledBoxExtent() / 50);

}

void UDebugVolumeVisualizerComponent::UpdateCapsulePreview()
{
	if (!DynamicMaterial)
	{
		PRINT(TAG_DEBUG_TDT, TDT_Warning, "UpdateCapsulePreview: Invalid DynamicMaterial, leaving early and unchanged.");
		return;
	}
	
	const UCapsuleComponent* component = Cast<UCapsuleComponent>(ParentShapeComponent);
	if (!component)
	{
		PRINT(TAG_DEBUG_TDT, TDT_Warning, "UpdateCapsulePreview: ParentShapeComponent is not of type UCapsuleComponent (is instead %s), leaving early and unchanged.", *ParentShapeComponent.GetClass()->GetName());
		return;
	}
	
	const float Radius = component->GetUnscaledCapsuleRadius();
	const float HalfHeight = component->GetUnscaledCapsuleHalfHeight();
	
	EnsureDebugHemisphereComponents();
	
	SetStaticMesh(CylinderPreviewMesh);
	SetMaterial(0, DynamicMaterial);
	
	SetRelativeLocation(FVector(0.0f));
	SetRelativeScale3D(FVector(Radius / 100, Radius / 100, (HalfHeight - Radius) / 100));

	for (int i = 0; i < 2; ++i)
	{
		UStaticMeshComponent* HemisphereComponent = DebugHemisphereComponents[i];
		if (!HemisphereComponent)
		{
			PRINT(TAG_DEBUG_TDT, TDT_Fatal, "INDEX %d IS NOT OF VALID TYPE USTATICMESHCOMPONENT.", i);
			continue;
		}

		HemisphereComponent->SetRelativeScale3D(
			FVector(
				Radius / 100,
				Radius / 100,
				(i == 0) ? Radius / 100 : -(Radius / 100)
			)
		);

		HemisphereComponent->SetRelativeLocation(
			FVector(
				0.0f,
				0.0f,
				(i == 0) ? HalfHeight - Radius : -(HalfHeight - Radius)
			)
		);
	}
}

void UDebugVolumeVisualizerComponent::UpdateSpherePreview()
{
	if (!DynamicMaterial)
	{
		PRINT(TAG_DEBUG_TDT, TDT_Warning, "UpdateSpherePreview: Invalid DynamicMaterial, leaving early and unchanged.");
		return;
	}
	
	const USphereComponent* component = Cast<USphereComponent>(ParentShapeComponent);
	if (!component)
	{
		PRINT(TAG_DEBUG_TDT, TDT_Warning, "UpdateSpherePreview: ParentShapeComponent is not of type USphereComponent (is instead %s), leaving early and unchanged.", *ParentShapeComponent.GetClass()->GetName());
		return;
	}
	
	const float Radius = component->GetUnscaledSphereRadius();
	
	EnsureDebugHemisphereComponents();
	
	SetStaticMesh(nullptr);
	SetMaterial(0, nullptr);
	
	SetRelativeLocation(FVector(0.0f));

	for (int i = 0; i < 2; ++i)
	{
		UStaticMeshComponent* HemisphereComponent = DebugHemisphereComponents[i];
		if (!HemisphereComponent)
		{
			PRINT(TAG_DEBUG_TDT, TDT_Fatal, "INDEX %d IS NOT OF VALID TYPE USTATICMESHCOMPONENT.", i);
			continue;
		}

		HemisphereComponent->SetRelativeScale3D(
			FVector(
				Radius / 100,
				Radius / 100,
				(i == 0) ? Radius / 100 : -(Radius / 100)
			)
		);

		HemisphereComponent->SetRelativeLocation(
			FVector(
				0.0f
			)
		);
	}
}

void UDebugVolumeVisualizerComponent::UpdatePreviewColor(const FLinearColor NewColor)
{
	if (DynamicMaterial)
	{
		DynamicMaterial->SetVectorParameterValue(
			TEXT("Preview_Colour"),
			NewColor
		);
	}
	
	Preview_Color = NewColor;
}
	
#endif

void UDebugVolumeVisualizerComponent::OnDebugDrawingChanged(const bool Enabled)
{
	if (AffectsShapeVisibility && ParentShapeComponent)
	{
		ParentShapeComponent->SetHiddenInGame(!Enabled);
	}
	if (AffectsActorVisibility)
	{
		GetOwner()->SetActorHiddenInGame(!Enabled);
	}
	
	SetHiddenInGame(!Enabled);
	
	for (const auto MeshComponent : DebugHemisphereComponents)
	{
		MeshComponent->SetHiddenInGame(!Enabled);
	}
}