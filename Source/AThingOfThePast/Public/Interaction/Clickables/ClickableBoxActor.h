// Copyright GCU 2026. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "ClickableBoxActor.generated.h"

UCLASS(Blueprintable)
class ATHINGOFTHEPAST_API AClickableBoxActor : public AActor
{
	GENERATED_BODY()
	
public:	
	AClickableBoxActor();
	
	UPROPERTY()
	TObjectPtr<UBoxComponent> ClickableBoxComponent;
	
	virtual void NotifyActorOnClicked(FKey ButtonPressed) override;

protected:
	virtual void BeginPlay() override;

};
