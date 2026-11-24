// Copyright Kara Brown 2026. All Rights Reserved.

#pragma once
//
// #include "CoreMinimal.h"
// #include "GameplayTagContainer.h"
// #include "TDTTypes.h"
// #include "Components/BoxComponent.h"
// #include "TPSVolume.generated.h"
//
// class UTPSDebugWidgetComponent;
// struct FTPSDebugValues;
//
// UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), AutoExpandCategories = ("Volume|Mesh", "Volume|Widget"), DisplayName = "TPS Box Component")
// class TPSEXPERIMENTAL_API UTPSVolume : public UBoxComponent
// {
//     GENERATED_BODY()
//     
// public:
//     
//     UTPSVolume();
//     
//     UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Volume", meta = (Categories = "Debug"))
//     FGameplayTagContainer DebugTags;
//     
//     UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Volume|Mesh")
//     TObjectPtr<UStaticMesh> PreviewMesh;
//     
//     UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Volume|Mesh")
//     TObjectPtr<UMaterialInterface> PreviewMaterial;
//     
//     UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Volume|Mesh")
//     FLinearColor Preview_Colour = FLinearColor::White;
//     
//     UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Volume|Widget")
//     bool EnableDebugWidget = true;
//     
//     UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Volume|Widget", meta = (EditCondition = "EnableDebugWidget"))
//     FText DefaultDebugText = INVTEXT("TPSVolume");
//     
//     UFUNCTION(BlueprintCallable, Category="Volume|Widget")
//     void SetDebugText(const FText InText);
//     
// protected:
//     
//     virtual void OnRegister() override;
//     virtual void OnUnregister() override;
//     
//     virtual void BeginPlay() override;
//     UFUNCTION(BlueprintNativeEvent) void OnDebugValueChanged(FDebugOutputSettings _debugValues);
//
// private:
//
//     UPROPERTY(Transient)
//     TObjectPtr<UStaticMeshComponent> VisualMeshComponent;
//
//     UPROPERTY(Transient)
//     TObjectPtr<UTPSDebugWidgetComponent> DebugWidgetComponent;
// };
