// Copyright Kara Brown 2026. All Rights Reserved.


#include "World/Widget/TDTDebugWidget.h"

#include "CommonTextBlock.h"
#include "Blueprint/WidgetTree.h"
#include "Messages/TDTMessagesLibrary.h"
#include "Settings/TDTConfigLibrary.h"

void UTDTDebugWidget::SetDebugText_Implementation(const FText& InText)
{
	if (TextBlock)
	{
		TextBlock->SetText(InText);
	}
	else
	{
		DefaultText = InText;
	}
}

void UTDTDebugWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
		
	TextBlock = WidgetTree->ConstructWidget<UTextBlock>(UTextBlock::StaticClass(), TEXT("Debug Text Block"));
	TextBlock->SetJustification(ETextJustify::Center);
	TextBlock->SetVisibility(ESlateVisibility::HitTestInvisible);
	TextBlock->SetText(DefaultText);
	WidgetTree->RootWidget = TextBlock;
	
	if (GEngine && GEngine->GameViewport)
	{
		GEngine->GameViewport->Viewport->ViewportResizedEvent.AddUObject(
			this,
			&UTDTDebugWidget::OnViewportResized
		);
	}

}

void UTDTDebugWidget::OnViewportResized(FViewport* Viewport, const uint32 NewSize) const
{
	if (TDTConfig::GetOutputConfig()->OverrideDefaultWidgetTextSize && GEngine && GEngine->GameViewport)
	{
		FVector2D ScreenSize;
		GEngine->GameViewport->GetViewportSize(ScreenSize);
		
		FSlateFontInfo NewFont = TextBlock->Font;
	
		NewFont.Size = FMath::Max((30.0f - ScreenSize.Y / 80.0f), 4.0f);
		NewFont.Size += TDTConfig::GetOutputConfig()->DefaultWidgetTextSize - 16.0f;
		
		if (ScreenSize.Y > 540.0f)
		{
			NewFont.OutlineSettings.OutlineSize = 1;
		}
		else
		{
			NewFont.OutlineSettings.OutlineSize = 2;
		}
		
		TextBlock->SetFont(NewFont);
		
		PRINT(TAG_DEBUG_TDT, TDT_Verbose, "Viewport resized called, updating font size to %f (Screen size X%f:Y%f)", NewFont.Size, ScreenSize.X, ScreenSize.Y);
	}
}

void UTDTDebugWidget::NativeConstruct()
{
	Super::NativeConstruct();
	
	if (TDTConfig::GetOutputConfig()->OverrideDefaultWidgetTextSize && GEngine && GEngine->GameViewport)
	{
		FVector2D ScreenSize;
		GEngine->GameViewport->GetViewportSize(ScreenSize);
		
		FSlateFontInfo NewFont = TextBlock->Font;
	
		NewFont.Size = FMath::Max((30.0f - ScreenSize.Y / 60.0f), 4.0f);
		NewFont.Size += TDTConfig::GetOutputConfig()->DefaultWidgetTextSize - 5.0f;
		
		if (ScreenSize.Y > 540.0f)
		{
			NewFont.OutlineSettings.OutlineSize = 1;
		}
		else
		{
			NewFont.OutlineSettings.OutlineSize = 2;
		}
		
		TextBlock->SetFont(NewFont);
	}
	
	GetWorld()->GetTimerManager().SetTimerForNextTick(
	FTimerDelegate::CreateLambda([this]
	{
		if (GEngine && GEngine->GameViewport)
		{
			OnViewportResized(GEngine->GameViewport->Viewport, 0);
		}
	}));
}