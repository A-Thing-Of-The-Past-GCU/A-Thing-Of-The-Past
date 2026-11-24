// Copyright Kara Brown 2026. All Rights Reserved.

#include "TDTEditor.h"

#include "Editor.h"
#include "TDTEditorStyle.h"
#include "TDTEditorCommands.h"
#include "Misc/MessageDialog.h"
#include "ToolMenus.h"
#include "EditorUtilityWidgetBlueprint.h"
#include "EditorUtilitySubsystem.h"
#include "ISettingsModule.h"

static const FName TDTEditorTabName("TDTEditor");

#define LOCTEXT_NAMESPACE "FTDTEditorModule"

void FTDTEditorModule::StartupModule()
{	
	FTDTEditorStyle::Initialize();
	FTDTEditorStyle::ReloadTextures();

	FTDTEditorCommands::Register();
	
	PluginCommands = MakeShareable(new FUICommandList);

	PluginCommands->MapAction(
		FTDTEditorCommands::Get().OpenTDTEditorUtility,
		FExecuteAction::CreateRaw(this, &FTDTEditorModule::OpenPerUserPreferences),
		FCanExecuteAction());

	PluginCommands->MapAction(
		FTDTEditorCommands::Get().OpenTDTEditorUtility2,
		FExecuteAction::CreateRaw(this, &FTDTEditorModule::OpenProjectPreferences),
		FCanExecuteAction());

	UToolMenus::RegisterStartupCallback(FSimpleMulticastDelegate::FDelegate::CreateRaw(this, &FTDTEditorModule::RegisterMenus));
}

void FTDTEditorModule::ShutdownModule()
{
	UToolMenus::UnRegisterStartupCallback(this);

	UToolMenus::UnregisterOwner(this);

	FTDTEditorStyle::Shutdown();

	FTDTEditorCommands::Unregister();
}

void FTDTEditorModule::OpenPerUserPreferences()
{
	ISettingsModule& SettingsModule =
	FModuleManager::LoadModuleChecked<ISettingsModule>("Settings");

	SettingsModule.ShowViewer(
		"Editor",        // Container
		"Plugins",       // Category
		"Toggleable Debug Tools"     // Section
	);
}

void FTDTEditorModule::OpenProjectPreferences()
{
	ISettingsModule& SettingsModule =
	FModuleManager::LoadModuleChecked<ISettingsModule>("Settings");

	SettingsModule.ShowViewer(
		"Project",        // Container
		"Plugins",       // Category
		"Toggleable Debug Tools"     // Section
	);
}

void FTDTEditorModule::RegisterMenus()
{
	FToolMenuOwnerScoped OwnerScoped(this);

	// Main Menu
	{
		UToolMenu* Menu =
			UToolMenus::Get()->ExtendMenu("LevelEditor.MainMenu.Tools");

		FToolMenuSection& Section =
			Menu->FindOrAddSection("Debugging");

		Section.Label =
			NSLOCTEXT("TDTEventsEditor", "Debugging", "Debugging");

		Section.AddMenuEntryWithCommandList(
			FTDTEditorCommands::Get().OpenTDTEditorUtility,
			PluginCommands
		);
	}

	// Toolbar
	{
		UToolMenu* ToolbarMenu =
			UToolMenus::Get()->ExtendMenu(
				"LevelEditor.LevelEditorToolBar.User"
			);

		FToolMenuSection& Section =
			ToolbarMenu->FindOrAddSection("TDTTools");

		FToolMenuEntry Entry = FToolMenuEntry::InitComboButton(
			"TDTToolsCombo",

			// Main button action
			FUIAction(),

			// Dropdown contents
			FOnGetContent::CreateLambda([this]()
			{
				FMenuBuilder MenuBuilder(true, PluginCommands);

				MenuBuilder.AddMenuEntry(
					FTDTEditorCommands::Get().OpenTDTEditorUtility
				);

				MenuBuilder.AddMenuEntry(
					FTDTEditorCommands::Get().OpenTDTEditorUtility2
				);

				return MenuBuilder.MakeWidget();
			}),

			LOCTEXT("TDTTools_Label","Debug Tools"),
			LOCTEXT("TDTTools_Tooltip","Open Debug Tools"),

			FSlateIcon(
				FTDTEditorStyle::GetStyleSetName(),
				"TDTEditor.Testing"
			)
		);

		Entry.StyleNameOverride = "CalloutToolbar";

		Section.AddEntry(Entry);
	}
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FTDTEditorModule, TDTEditor)