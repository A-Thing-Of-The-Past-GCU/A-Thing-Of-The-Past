// Copyright GCU 2026. All rights reserved.
//Gets inspects header and the player controller components so they can be used to stop the player.
#include "inspects.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"

AInspects::AInspects()
{
	//Allows us to use tick so we can move the object to the camera
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = false;
	//Allows us to use the object after we are finished inspecting it
	DestroyAfterInteraction = false;
	DisableInteractionsAfterInteraction = false;
}
//Calls the blueprint class for interaction and StartInspect.
void AInspects::OnInteraction_Implementation(AActor* Player)
{
	Super::OnInteraction_Implementation(Player);
	StartInspect(Player);
}

void AInspects::StartInspect(AActor* Player)
{
	//If the player is inspecting stop the function here.
	if (Inspecting == true)
	{
		return;
	}
	//Get player controller 0 and set inspecting to true.
	InspectController = UGameplayStatics::GetPlayerController(this, 0);
	Inspecting = true;

	//Put this in cause I thought I would have started the rotation by now oops.
	OGLocation = GetActorLocation();
	OGRotation = GetActorRotation();

	//Allows us to stop the character later.
	ACharacter* DefaultCharacter = Cast<ACharacter>(InspectController->GetPawn());
	//Stop the character
	if (DefaultCharacter)
	{
		DefaultCharacter
			->GetCharacterMovement()
			->DisableMovement();
	}

	//Set item collision to false
	SetActorEnableCollision(false);

	//Call moveobjectposition
	MoveObjectPosition();

	//Set the item to be able to tick.
	SetActorTickEnabled(true);
}

void AInspects::StopInspect()
{
	//If you are inspecting dont go any further.
	if (!Inspecting)
	{
		return;
	}
	//Set inspecting to false.
	Inspecting = false;

	//Set the item back to its default position and set its tick back to false.
	SetActorTickEnabled(false);
	SetActorLocation(OGLocation);
	SetActorRotation(OGRotation);

	//Set it so you can collide with it again.
	SetActorEnableCollision(true);

	//Let the character walk again.
	if (InspectController)
	{
		ACharacter* PlayerCharacter =
			Cast<ACharacter>(InspectController->GetPawn());

		if (PlayerCharacter)
		{
			PlayerCharacter
				->GetCharacterMovement()
				->SetMovementMode(MOVE_Walking);
		}
	}

	
	InspectController = nullptr;
}

void AInspects::MoveObjectPosition()
{
	//Get current camera location and rotation, store them and let the item sit distancefromcamera away from it.
		if (!InspectController)
		{
			return;
		}
	FVector CameraLocation;
	FRotator CameraRotation;
	
	InspectController->GetPlayerViewPoint(
		CameraLocation,
		CameraRotation
	);

	
	FVector InspectingItemLocation =
		CameraLocation +
		(CameraRotation.Vector() * DistancefromCamera);

	
	SetActorLocation(InspectingItemLocation);
}

void AInspects::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	
	if (Inspecting)
	{
		MoveObjectPosition();
	}
}