// Copyright GCU 2026. All rights reserved.


#include "ExampleActor.h"

// Sets default values
AExampleActor::AExampleActor()
{
	BlueprintAccessibleString = "Default String Text";
}

// Called when the game starts or when spawned
void AExampleActor::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AExampleActor::Tick(const float DeltaTime)
{
	Super::Tick(DeltaTime);
}

FString AExampleActor::GetBlueprintAccessibleString()
{
	return BlueprintAccessibleString;
}

