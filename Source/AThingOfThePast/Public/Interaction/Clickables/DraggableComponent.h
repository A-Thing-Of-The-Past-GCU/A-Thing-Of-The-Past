// Copyright GCU 2026. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/SphereComponent.h"
#include "Components/WidgetComponent.h"
#include "GameFramework/Actor.h"
#include "DraggableComponent.generated.h"

UCLASS(ClassGroup=(AThingOfThePast), meta=(BlueprintSpawnableComponent))
class ATHINGOFTHEPAST_API UDraggableComponent : public UWidgetComponent
{
	GENERATED_BODY()
	
public:	
	
	UDraggableComponent();

	
#pragma region Interaction
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Configuration|Interaction")
	TSubclassOf<UUserWidget> TelegraphingWidget;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Configuration|Interaction")
	float SphereRadius = 15.0f;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Configuration|Interaction", AdvancedDisplay)
	FTransform TelegraphingWidgetTransform = FTransform::Identity;
	
#pragma endregion
	
	
#pragma region Transient
	
	UPROPERTY(Transient, BlueprintReadOnly, VisibleAnywhere, Category = "Configuration|Interaction")
	bool Enabled = false;
	
	UPROPERTY(Transient, BlueprintReadOnly, VisibleAnywhere, Category = "Configuration|Interaction")
	FVector2D TargetClickedCursorLocation = FVector2D::ZeroVector;
	
	/**Unreal really doesn't like ActorComponents keeping track of their own children, 
	 * so on Register we create our components, and on unregister we clear them*/
	
	UPROPERTY(Transient)
	TObjectPtr<USphereComponent> InteractionTarget;
	
	UPROPERTY(Transient)
	TObjectPtr<UWidgetComponent> InteractionWidget;
	
	UPROPERTY(Transient)
	TObjectPtr<UWidgetComponent> InteractionTelegraphWidget;
	
    /**Used to manage the lifetime of the child components*/
	
	virtual void OnRegister() override;
	virtual void OnUnregister() override;
	
#pragma endregion 
	
	UFUNCTION()
	void OnTargetClicked(UPrimitiveComponent* TouchedComponent , FKey ButtonPressed);
	
	UFUNCTION()
	void OnTargetReleased(UPrimitiveComponent* TouchedComponent, FKey ButtonReleased);
	
#pragma region Logic
	
	UFUNCTION(BlueprintCallable)
	void SetDragStrength(const FVector2D DragStrength);
	
	/** Desired drag angle (0 = 12:00. 90 = 03:00) */
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
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Configuration, meta = (UIMin = 0, UIMax = 1, EditCondition = UseTargetStrengthToleranceFalloff))
	float TargetStrengthToleranceFalloff = 0.25f;
	
	//
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Configuration)
	float AlphaMin = 0.0f;
	
	// 
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Configuration)
	float AlphaMax = 1.0f;
	
	//ToDo: Use this to prevent recursive changes to the position on slightly off inputs. 
	//Player input after being processed for the visible display.
	UPROPERTY(BlueprintReadOnly, Category = Output)
	FVector2D VisibleOutputVector;
	
	//Player input after being processed.
	UPROPERTY(BlueprintReadOnly, Category = Output)
	FVector2D OutputVector;
	
	//Player input after being processed and measured.
	UPROPERTY(BlueprintReadOnly, Category = Output)
	float OutputAlpha;
	
#pragma endregion 

	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

};
