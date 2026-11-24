// Copyright Kara Brown 2026. All Rights Reserved.

#pragma once


#include "CoreMinimal.h"
#include "GameFramework/CheatManager.h"
#include "TDTCheatManager.generated.h"



UCLASS(Blueprintable, BlueprintType)
class TDT_API UTDTCheatManager : public UCheatManager
{
	GENERATED_BODY()
	
protected:
	bool bDebugMenuOpen = false;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Toggleable Debug Tools|DebugMenu")
	UUserWidget* DebugMenuWidget;
public:
	virtual void InitCheatManager() override;
	
	UFUNCTION(BlueprintNativeEvent, Category="Toggleable Debug Tools|DebugMenu")
	void OnDebugKeyPressed();
};

