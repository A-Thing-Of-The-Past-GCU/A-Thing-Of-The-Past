// Copyright GCU 2026. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Interaction/Interactable.h"
#include "ItemDefinition.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType, Category = "Items")
class ATHINGOFTHEPAST_API UItemDefinition : public UPrimaryDataAsset
{
	GENERATED_BODY()
	
public:
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, NoClear) 
	FText DisplayName = INVTEXT("Default Item");
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TSubclassOf<UItemDefinition> SlotDefinitionExample;
	
	/***/
	UPROPERTY(BlueprintReadWrite, EditAnywhere) 
	TArray<FGameplayTag> Item;
	
	/** Intended to be used as an easy check for if an item can fulful a purpose.
	 * e.g. a locked door checks for an item type Item.Key.Room1 || Item.Key.Master
	 * and then allows access, */
	UPROPERTY(BlueprintReadWrite, EditAnywhere) 
	TArray<FGameplayTag> ItemTypes;
	
	//Ideally i would want some components, stack count etc but the design isn't really there yet for that.
	
protected:
	
	UPROPERTY(EditDefaultsOnly) FString DeveloperComment;
};
