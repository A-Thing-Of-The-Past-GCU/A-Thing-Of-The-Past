#pragma once

#include "CoreMinimal.h"
#include "Interaction/Interactable.h"
#include "inspects.generated.h"

class APlayerController;

UCLASS()
class ATHINGOFTHEPAST_API AInspects : public AInteractable
{
	GENERATED_BODY()

public:
	AInspects();

	virtual void Tick(float DeltaTime) override;
	virtual void OnInteraction_Implementation(AActor* Player) override;

	//Makes it so start and stopinspect can be called from blueprints to link up to the game.

	UFUNCTION(BlueprintCallable)
	void StartInspect(AActor* Player);

	UFUNCTION(BlueprintCallable)
	void StopInspect();

	//Create variables for the item.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inspect")
	FString ItemName = "Hammer";

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inspect")
	FString ItemDescription = "HammerDescription";

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inspect")
	float DistancefromCamera = 150.0f;

	UPROPERTY(BlueprintReadOnly, Category = "Inspect")
	bool Inspecting = false;

private:
	void MoveObjectPosition();

	// Stores where the item was before inspection
	FVector OGLocation;
	FRotator OGRotation;

	// Stores the controller so the camera and player movement can be accessed
	APlayerController* InspectController = nullptr;
};