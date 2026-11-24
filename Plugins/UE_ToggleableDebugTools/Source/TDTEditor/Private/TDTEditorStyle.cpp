// Copyright Kara Brown 2026. All Rights Reserved.

#include "TDTEditorStyle.h"
#include "TDTEditor.h"
#include "Framework/Application/SlateApplication.h"
#include "Styling/SlateStyleRegistry.h"
#include "Slate/SlateGameResources.h"
#include "Interfaces/IPluginManager.h"
#include "Styling/SlateStyleMacros.h"

#define RootToContentDir Style->RootToContentDir

TSharedPtr<FSlateStyleSet> FTDTEditorStyle::StyleInstance = nullptr;

void FTDTEditorStyle::Initialize()
{
	if (!StyleInstance.IsValid())
	{
		StyleInstance = Create();
		FSlateStyleRegistry::RegisterSlateStyle(*StyleInstance);
	}
}

void FTDTEditorStyle::Shutdown()
{
	FSlateStyleRegistry::UnRegisterSlateStyle(*StyleInstance);
	ensure(StyleInstance.IsUnique());
	StyleInstance.Reset();
}

FName FTDTEditorStyle::GetStyleSetName()
{
	static FName StyleSetName(TEXT("TDTEditorStyle"));
	return StyleSetName;
}


const FVector2D Icon16x16(16.0f, 16.0f);
const FVector2D Icon20x20(20.0f, 20.0f);

TSharedRef< FSlateStyleSet > FTDTEditorStyle::Create()
{
	TSharedRef< FSlateStyleSet > Style = MakeShareable(new FSlateStyleSet("TDTEditorStyle"));
	Style->SetContentRoot(IPluginManager::Get().FindPlugin("TDT")->GetBaseDir() / TEXT("Resources"));

	Style->Set("TDTEditor.Testing", new IMAGE_BRUSH_SVG(TEXT("SVG_ToggleableDebugTools"),Icon20x20));
	// Style->Set("TDTEditor.OpenTDTEditorUtility", new IMAGE_BRUSH_SVG(TEXT("SVG_ToggleableDebugTools"), Icon20x20));
	// Style->Set("TDTEditor.OpenTDTEditorUtility2", new IMAGE_BRUSH_SVG(TEXT("SVG_ToggleableDebugTools"), Icon20x20));
	return Style;
}

void FTDTEditorStyle::ReloadTextures()
{
	if (FSlateApplication::IsInitialized())
	{
		FSlateApplication::Get().GetRenderer()->ReloadTextureResources();
	}
}

const ISlateStyle& FTDTEditorStyle::Get()
{
	return *StyleInstance;
}
