// Copyright Kara Brown 2026. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Framework/Commands/Commands.h"
#include "TDTEditorStyle.h"

class FTDTEditorCommands : public TCommands<FTDTEditorCommands>
{
public:

	FTDTEditorCommands()
		: TCommands<FTDTEditorCommands>(TEXT("TDTEditor"), NSLOCTEXT("Contexts", "TDTEditor", "TDTEditor Plugin"), NAME_None, FTDTEditorStyle::GetStyleSetName())
	{
	}

	// TCommands<> interface
	virtual void RegisterCommands() override;

public:
	TSharedPtr< FUICommandInfo > OpenTDTEditorUtility;
	TSharedPtr< FUICommandInfo > OpenTDTEditorUtility2;
};
