// Copyright Kara Brown 2026. All Rights Reserved.

#include "TDTEditorCommands.h"

#define LOCTEXT_NAMESPACE "FTDTSplinesModule"

void FTDTEditorCommands::RegisterCommands()
{
	UI_COMMAND(OpenTDTEditorUtility, "User Preferences (Print Strings + Logs)", "Execute TDT action", EUserInterfaceActionType::Button, FInputChord());
	UI_COMMAND(OpenTDTEditorUtility2, "Project Preferences (Print String Colors)", "Execute TDT action 2", EUserInterfaceActionType::Button, FInputChord());
}

#undef LOCTEXT_NAMESPACE
