// Copyright Kara Brown 2026. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Components/StaticMeshComponent.h"
#include "TDTDebugVolumeVisualizerComponent.generated.h"

class UDebugTextWidgetComponent;

/**
 * Visualizes the shape of the parent ShapeComponent using debug meshes and an optional debug widget.
 *
 * Supports visualization of box, sphere, and capsule shapes. Its visibility, including that
 * of the attached debug widget, is controlled by the configured DebugTag.
 *
 * @see UTDTWorldLibrary
 */
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), AutoExpandCategories = ("Debug", "Volume|Widget"), DisplayName = "Debug Volume Visualizer", HideCategories = (StaticMesh, Materials))
class TDT_API UDebugVolumeVisualizerComponent : public UStaticMeshComponent
{
    GENERATED_BODY()
    
public:
    
    UDebugVolumeVisualizerComponent();
    
    /** Gameplay tag used to control whether this debug volume and its attached widget are displayed. */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Debug", meta=(Categories="Debug"))
    FGameplayTag DebugTag;
    
    /** Color used to render the volume preview. */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Debug")
    FLinearColor Preview_Color = FLinearColor(0.25f, 0.25f, 0.25f);
    
    /** Whether a debug widget should be attached to and displayed with the volume. */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Debug")
    bool EnableDebugWidget = false;
    
    /** Default text displayed by the attached debug widget. */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Debug", meta=(EditCondition="EnableDebugWidget"))
    FText DefaultText = INVTEXT("TDT Volume");
    
    /** Should control whether this component's attach parent is displayed. */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Debug")
    bool AffectsShapeVisibility = true;
    
    /** Should control whether this component's actor parent is displayed. */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Debug")
    bool AffectsActorVisibility = false;
    
protected:
    
    /** The component whose shape, transform, and bounds are used to determine the preview volume. */
    UPROPERTY(Transient)
    TObjectPtr<USceneComponent> ParentShapeComponent;
    
    /** Static mesh used to preview box-shaped volumes. */
    UPROPERTY(VisibleAnywhere, Category="Volume", meta=(AdvancedDisplay))
    TObjectPtr<UStaticMesh> BoxPreviewMesh;
    
    /** Static mesh used to preview hemisphere-shaped volumes. */
    UPROPERTY(VisibleAnywhere, Category="Volume", meta=(AdvancedDisplay))
    TObjectPtr<UStaticMesh> HemispherePreviewMesh;
    
    /** Static mesh used to preview cylinder-shaped volumes. */
    UPROPERTY(VisibleAnywhere, Category="Volume", meta=(AdvancedDisplay))
    TObjectPtr<UStaticMesh> CylinderPreviewMesh;
    
    /** Material applied to the volume preview mesh. */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Volume|Mesh")
    TObjectPtr<UMaterialInterface> PreviewMaterial;
    
    UPROPERTY(Transient)
    TObjectPtr<UMaterialInstanceDynamic> DynamicMaterial;

    UPROPERTY(Transient)
    TObjectPtr<UDebugTextWidgetComponent> DebugWidgetComponent;

    UPROPERTY(Transient)
    TArray<TObjectPtr<UStaticMeshComponent>> DebugHemisphereComponents;
    
public:
    
    /** Sets the text displayed by the attached debug widget. */
    UFUNCTION(BlueprintCallable, Category="Volume|Widget")
    void SetDebugText(const FText InText);
    
    /** Updates the preview mesh, transform, and associated components to match the parent shape. */
    UFUNCTION(BlueprintCallable, Category = TDT)
    void UpdatePreview();
    
protected:
    
    virtual void BeginPlay() override;

#if !(UE_BUILD_SHIPPING || UE_BUILD_TEST)
    
    void UpdateBoxPreview();
    void UpdateCapsulePreview();
    void UpdateSpherePreview();
    
    void UpdatePreviewColor(FLinearColor NewColor);
    
    virtual void OnRegister() override;
    virtual void OnUnregister() override;

    void EnsureDebugHemisphereComponents();
    void EnsureDestroyDebugHemisphereComponents();

    void EnsureDebugWidgetComponent();
    void EnsureDestroyDebugWidgetComponent();
	
#endif
    
    /** Internally used to set visibility. */
    UFUNCTION()
    void OnDebugDrawingChanged(bool Enabled);

};
