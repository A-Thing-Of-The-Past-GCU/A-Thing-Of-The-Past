// Copyright GCU 2026. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "InteractableInterface.h"
#include "GameFramework/Actor.h"
#include "Interactable.generated.h"

UCLASS(Blueprintable)
class ATHINGOFTHEPAST_API AInteractable : public AActor, public IInteractableInterface
{
	GENERATED_BODY()
	
public:	
	AInteractable();
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Interaction")
	bool InteractionsEnabled = true;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Interaction", AdvancedDisplay)
	bool DisableInteractionsAfterInteraction = true;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Interaction", AdvancedDisplay)
	bool DestroyAfterInteraction = false;

protected:
	virtual void BeginPlay() override;
	
public:
	
	virtual bool CanInteract_Implementation(AActor* Player) override;
	virtual bool AttemptInteract_Implementation(AActor* Player) override;
	virtual void OnInteraction_Implementation(AActor* Player) override;

};
