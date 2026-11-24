// Copyright Kara Brown 2026. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "TDTWidgetInterface.generated.h"

UINTERFACE()
class UTDTWidgetInterface : public UInterface
{
	GENERATED_BODY()
};

class TDT_API ITDTWidgetInterface
{
	GENERATED_BODY()

public:
	
	UFUNCTION(BlueprintNativeEvent, Category = "Toggleable Debug Tools|Widget")
	void SetDebugText(const FText& InText = INVTEXT("Default"));
};
