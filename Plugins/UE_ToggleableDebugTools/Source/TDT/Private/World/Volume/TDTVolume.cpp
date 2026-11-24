// // Copyright Kara Brown 2026. All Rights Reserved.
//
//
// #include "TPSVolume.h"
//
// #include "TogglePrintStringsLibrary.h"
// #include "TPSDebugWidgetComponent.h"
//
// UTPSVolume::UTPSVolume()
// {
// 	BoxExtent = FVector(50.0f);
// 	
// #if !(UE_BUILD_SHIPPING || UE_BUILD_TEST)
// 	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshFinder(
// 	TEXT("/Engine/BasicShapes/Cube.Cube"));
// 	
// 	if (MeshFinder.Succeeded())
// 	{
// 		PreviewMesh = MeshFinder.Object;
// 	}
// 	
// 	static ConstructorHelpers::FObjectFinder<UMaterialInterface> MaterialFinder(
// 		TEXT("/TPSExperimental/MI_DebugFieldRadius.MI_DebugFieldRadius")
// 	);
//
// 	if (MaterialFinder.Succeeded())
// 	{
// 		PreviewMaterial = MaterialFinder.Object;
// 	}
// 	
// 	DebugTags = FGameplayTagContainer(TAG_DEBUG_World);
// #endif
// }
//
// void UTPSVolume::SetDebugText(const FText InText)
// {
// 	if (!EnableDebugWidget) return;
// 	if (!DebugWidgetComponent) return;
// 	DebugWidgetComponent->SetDebugText(InText);
// }
//
// void UTPSVolume::OnRegister()
// {
// 	Super::OnRegister();
//
// #if !(UE_BUILD_SHIPPING || UE_BUILD_TEST)
// 	// Dynamically spawn the visual mesh when registered
// 	
// 	if (!GetWorld())
// 	{
// 		return;
// 	}
// 	
// 	if (!VisualMeshComponent)
// 	{
// 		// 'this' sets the BoxComponent as the Outer for Garbage Collection
// 		VisualMeshComponent = NewObject<UStaticMeshComponent>(this, TEXT("VisualMeshInternal"));
//         
// 		if (VisualMeshComponent)
// 		{
// 			VisualMeshComponent->RegisterComponent();
// 			
// 			VisualMeshComponent->AttachToComponent(this, FAttachmentTransformRules::KeepRelativeTransform);
// 			VisualMeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
// 			VisualMeshComponent->SetCastShadow(false);
// 			
// 			VisualMeshComponent->SetStaticMesh(PreviewMesh);
// 			VisualMeshComponent->SetRelativeScale3D(FVector(GetUnscaledBoxExtent()/50));
// 			VisualMeshComponent->SetHiddenInGame(true);
// 			
// 			UMaterialInstanceDynamic* DynamicMaterial = UMaterialInstanceDynamic::Create(
// 				PreviewMaterial,
// 				this
// 			);
//
// 			if (DynamicMaterial)
// 			{
// 				DynamicMaterial->SetVectorParameterValue(
// 					TEXT("Preview_Colour"),
// 					Preview_Colour
// 				);
// 				DynamicMaterial->SetScalarParameterValue(FName("AlphaMax"), 0.8f);
// 				DynamicMaterial->SetScalarParameterValue(FName("AlphaMin"), 0.02f);
// 				DynamicMaterial->SetScalarParameterValue(FName("PulseLevel"), 1.25f);
//
// 				VisualMeshComponent->SetMaterial(
// 					0,
// 					DynamicMaterial
// 				);
// 			}
// 		}
// 	}
// 	
// 	if (EnableDebugWidget)
// 	{
// 		if (!DebugWidgetComponent)
// 		{
// 			DebugWidgetComponent = NewObject<UTPSDebugWidgetComponent>(this, TEXT("DebugWidgetInternal"));
//         
// 			if (DebugWidgetComponent)
// 			{
// 				DebugWidgetComponent->DebugTags = DebugTags;
// 				DebugWidgetComponent->DefaultDebugText = DefaultDebugText;
// 			
// 				DebugWidgetComponent->RegisterComponent();
// 			
// 				DebugWidgetComponent->AttachToComponent(this, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
// 				DebugWidgetComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
// 				DebugWidgetComponent->SetCastShadow(false);
// 			
// 				DebugWidgetComponent->SetHiddenInGame(true);
// 			}
// 		}
// 		else 
// 		{
// 			DebugWidgetComponent->DebugTags = DebugTags;
// 			DebugWidgetComponent->DefaultDebugText = DefaultDebugText;
// 		}
// 	}
// 	else
// 	{
// 		if (DebugWidgetComponent)
// 		{
// 			DebugWidgetComponent->DestroyComponent();
// 			DebugWidgetComponent = nullptr;
// 		}
// 	}
// #endif
// }
//
// void UTPSVolume::OnUnregister()
// {
// 	if (VisualMeshComponent)
// 	{
// 		VisualMeshComponent->DestroyComponent();
// 		VisualMeshComponent = nullptr;
// 	}
// 	
// 	if (DebugWidgetComponent)
// 	{
// 		DebugWidgetComponent->DestroyComponent();
// 		DebugWidgetComponent = nullptr;
// 	}
//
// 	Super::OnUnregister();
// }
//
// void UTPSVolume::BeginPlay()
// {
// 	Super::BeginPlay();
// 	
// #if !(UE_BUILD_SHIPPING || UE_BUILD_TEST)
// 	
// 	FDebugValueChangedCallback Callback;
// 	Callback.BindUFunction(this, FName("OnDebugValueChanged"));
// 	
// 	TPS::BindEventToOnDebugValuesChanged(DebugTags, Callback);
// 	
// #endif
// }
//
// void UTPSVolume::OnDebugValueChanged_Implementation(const FDebugOutputSettings _debugValues)
// {
// 	SetHiddenInGame(!_debugValues.printingEnabled);
// 	VisualMeshComponent->SetHiddenInGame(!_debugValues.printingEnabled);
// }
