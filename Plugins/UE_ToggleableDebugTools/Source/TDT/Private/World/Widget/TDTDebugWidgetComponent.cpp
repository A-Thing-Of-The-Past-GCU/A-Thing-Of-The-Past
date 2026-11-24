// Copyright Kara Brown 2026. All Rights Reserved.

#include "World/Widget/TDTDebugWidgetComponent.h"

#include "World/TDTWorldLibrary.h"
#include "World/Widget/TDTDebugWidget.h"

UDebugTextWidgetComponent::UDebugTextWidgetComponent(
	const FObjectInitializer& ObjectInitializer
)
	: Super(ObjectInitializer)
{
#if !(UE_BUILD_SHIPPING || UE_BUILD_TEST)
	
	SetWidgetSpace(EWidgetSpace::Screen);
	SetDrawAtDesiredSize(true);
	DebugWidgetClass = UTDTDebugWidget::StaticClass();
	WidgetClass = DebugWidgetClass;
	
	static ConstructorHelpers::FObjectFinder<UObject> TextObjectFinder(TEXT("/Engine/EngineFonts/Roboto.Roboto"));
	
	if (TextObjectFinder.Succeeded())
	{
		Font.FontObject = TextObjectFinder.Object;
	}
	
	Font.Size = 12;
	Font.OutlineSettings.OutlineSize = 1;
	Font.OutlineSettings.OutlineColor = FLinearColor::Black;
	
#endif
	SetHiddenInGame(true);
}

void UDebugTextWidgetComponent::BeginPlay()
{
	Super::BeginPlay();
	
#if !(UE_BUILD_SHIPPING || UE_BUILD_TEST)

	if (const auto DebugWidget = Cast<UTDTDebugWidget>(GetWidget()))
	{
		DebugWidget->TextBlock->SetFont(Font);
	}
	
	FDebugDrawingEnabledChangedCallback Callback;
	Callback.BindUFunction(this, FName("OnDebugValueChanged"));
	
	TDTWorld::BindToDebugDrawingEnabledChanged(DebugTag, Callback, true);
	
	if (GetWidget())
	{
		SetDebugText(DefaultText);
	}
	
#endif
}

void UDebugTextWidgetComponent::SetDebugText(const FText InText)
{
	if (GetWidget() && GetWidget()->Implements<UTDTWidgetInterface>())
	{
		ITDTWidgetInterface::Execute_SetDebugText(GetWidget(), InText);
	}
}

void UDebugTextWidgetComponent::OnDebugValueChanged_Implementation(const bool DebugDrawEnabled)
{
	SetHiddenInGame(!DebugDrawEnabled);
}
