// Copyright Kara Brown 2026. All Rights Reserved.


#include "Sample/TDTCheatManager.h"

//#include "TDTConfig.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "GameFramework/PlayerController.h"
#include "Components/InputComponent.h"
#include "TimerManager.h"
//#include "TDTLibrary.h"
#include "Messages/TDTMessagesLibrary.h"

void UTDTCheatManager::InitCheatManager()
{
	Super::InitCheatManager();

	GetWorld()->GetTimerManager().SetTimerForNextTick([this]
	{
		if (const APlayerController* PC = GetOuterAPlayerController())
		{
			if (!PC->InputComponent)
			{
				return;
			}
			PC->InputComponent->BindKey(EKeys::RightAlt, IE_Pressed, this, &UTDTCheatManager::OnDebugKeyPressed);
		}
	});
	
}

void UTDTCheatManager::OnDebugKeyPressed_Implementation()
{
	APlayerController* PC = GetOuterAPlayerController();
	if (!PC) return;
	
	const auto TDTConfig = TDTConfig::GetDisplayConfig();
	if (!TDTConfig) return;
	
	if (!TDTConfig->DebugMenuWidget.LoadSynchronous()) return;
	if (!DebugMenuWidget) DebugMenuWidget = NewObject<UUserWidget>(this, TDTConfig->DebugMenuWidget.Get());
	if (bDebugMenuOpen)
	{
		bDebugMenuOpen = false;
		UWidgetBlueprintLibrary::SetInputMode_GameOnly(PC);
		PC->SetShowMouseCursor(false);
		DebugMenuWidget->RemoveFromParent();
	}
	else
	{
		bDebugMenuOpen = true;
		UWidgetBlueprintLibrary::SetInputMode_GameAndUIEx(PC);
		PC->SetShowMouseCursor(true);
		DebugMenuWidget->AddToViewport(99999);
		
		FEventReply reply;
		UWidgetBlueprintLibrary::SetUserFocus(reply, DebugMenuWidget, false);
	}
}
