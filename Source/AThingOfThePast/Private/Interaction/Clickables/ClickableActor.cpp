// Copyright GCU 2026. All rights reserved.


#include "Interaction/Clickables/ClickableBoxActor.h"

AClickableBoxActor::AClickableBoxActor()
{
	PrimaryActorTick.bCanEverTick = true;

	ClickableBoxComponent = CreateDefaultSubobject<UBoxComponent>("ClickableBoxComponent");
	ClickableBoxComponent->SetupAttachment(RootComponent);
}

void AClickableBoxActor::BeginPlay()
{
	Super::BeginPlay();
}

void AClickableBoxActor::NotifyActorOnClicked(FKey ButtonPressed)
{
	Super::NotifyActorOnClicked(ButtonPressed);
}

