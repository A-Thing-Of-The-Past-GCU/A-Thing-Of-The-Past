// Copyright GCU 2026. All rights reserved.

#pragma once

#include "CoreMinimal.h"

#include "PuzzleTypes.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPuzzleSolvedChanged, bool, NewSolved);


UENUM(Blueprintable)
enum class EMyEnum : uint8
{
	A,
	B,
	C
};
