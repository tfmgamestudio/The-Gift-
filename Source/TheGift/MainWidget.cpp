// Fill out your copyright notice in the Description page of Project Settings.


#include "MainWidget.h"

void UMainWidget::SetUp(ATheGiftCharacter* PlayerCharacter)
{
	if (!PlayerCharacter)
		return;

	
	InteractWidget->SetVisibility(ESlateVisibility::Hidden);
}