// Copyright GCU 2026. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ExampleActor.generated.h"

UCLASS()
class ATHINGOFTHEPAST_API AExampleActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Constructor, sets default values for this actor's properties
	AExampleActor();

protected:
	// Called when the game starts or when spawned (Unity Equivalent: Start())
	virtual void BeginPlay() override;

public:	
	// Called every frame (Unity Equivalent: Update())
	virtual void Tick(float DeltaTime) override;
	
	// Blueprint editable string
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FString BlueprintAccessibleString;
	
	// Blueprint callable function
	UFUNCTION(BlueprintCallable)
	FString GetBlueprintAccessibleString();
	
	// Hold a reference to an actor
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	AActor* ActorPtr = this;
};
