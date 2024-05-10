// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractWidget.h"

void UInteractWidget::SetUp(ATheGiftCharacter* PlayerCharacter)
{
	if (!PlayerCharacter)
		return;

	this->SetVisibility(ESlateVisibility::Hidden);
}