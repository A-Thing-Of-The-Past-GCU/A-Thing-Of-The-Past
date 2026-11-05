// Copyright GCU 2026. All rights reserved.


#include "Puzzles/PuzzleCoordinator.h"

#include "Components/BillboardComponent.h"
#include "Puzzles/PuzzleSolution.h"

APuzzleCoordinator::APuzzleCoordinator()
{
	PrimaryActorTick.bCanEverTick = false;
	
#if WITH_EDITORONLY_DATA
	
	EditorBillboard = CreateDefaultSubobject<UBillboardComponent>(TEXT("Editor Billboard"));	
	RootComponent = EditorBillboard;
	
	static ConstructorHelpers::FObjectFinder<UTexture2D> TextureAsset(
	TEXT("/Game/Game/Puzzles/T_PuzzleCoordinator.T_PuzzleCoordinator")
	);

	if (TextureAsset.Succeeded())
	{
		EditorBillboard->SetSprite(TextureAsset.Object);
	}
	
#endif


}

void APuzzleCoordinator::SetSolved(const bool NewSolved)
{
	if (bSolved == NewSolved)
	{
		return;
	}
	
	bSolved = NewSolved;

	for (auto OutputActor : OutputActors)
	{
		if (!IsValid(OutputActor) || !OutputActor->Implements<UPuzzleSolution>())
		{
			continue;
		}
		
		IPuzzleSolution::Execute_OnPuzzleSolvedUpdated(OutputActor, NewSolved);
	}
	
	OnSolvedChanged.Broadcast(bSolved);
}

void APuzzleCoordinator::BeginPlay()
{
	Super::BeginPlay();

	for (auto PuzzleActor : PuzzleActors)
	{
		if (!PuzzleActor)
		{
			continue;
		}
		
		auto Solver = PuzzleActor->GetComponentByClass<UPuzzleSolverComponent>();
		
		if (!Solver)
		{
			continue;
		}
		
		SolverComponents.Add(Solver);
	}

	for (const auto SolverComponent : SolverComponents)
	{
		SolverComponent->OnSolvedChanged.AddUniqueDynamic(this, &APuzzleCoordinator::OnComponentSolvedChanged);
	}
	
}

void APuzzleCoordinator::OnComponentSolvedChanged_Implementation(const bool NewSolved)
{
	for (const auto SolverComponent : SolverComponents)
	{
		if (SolverComponent->bSolved == bSolved)
		{
			return;
		}
	}
	
	SetSolved(NewSolved);
}

