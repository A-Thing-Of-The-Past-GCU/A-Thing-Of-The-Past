// Copyright Kara Brown 2026. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

class FTDTEditorModule : public IModuleInterface
{
public:

    virtual void StartupModule() override;
    virtual void ShutdownModule() override;
	
    // void PluginButtonClicked();
    void OpenProjectPreferences();
    void OpenPerUserPreferences();
	
private:

    void RegisterMenus();


private:
    TSharedPtr<class FUICommandList> PluginCommands;
};