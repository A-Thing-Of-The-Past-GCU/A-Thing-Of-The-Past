// Copyright GCU 2026. All rights reserved.


#include "Interaction/Clickables/CursorInteractionPromptWidget.h"

void UCursorInteractionPromptWidget::AssignOverlapPrimitive(UPrimitiveComponent* OverlapPrimitive)
{
	if (!OverlapPrimitive) return;
	OverlapPrimitives.Add(OverlapPrimitive);
		
	OverlapPrimitive->OnBeginCursorOver.AddUniqueDynamic(this, &UCursorInteractionPromptWidget::OnBeginCursorOver);
	OverlapPrimitive->OnEndCursorOver.AddUniqueDynamic(this, &UCursorInteractionPromptWidget::OnEndCursorOver);
}

void UCursorInteractionPromptWidget::OnBeginCursorOver_Implementation(UPrimitiveComponent* TouchedComponent)
{
}

void UCursorInteractionPromptWidget::OnEndCursorOver_Implementation(UPrimitiveComponent* TouchedComponent)
{
}
