// Fill out your copyright notice in the Description page of Project Settings.


#include "ModelViewerWidget.h"

#include "Kismet/GameplayStatics.h"

void UModelViewerWidget::SetUp(ATheGiftCharacter* playerCharacter)
{
	if (!playerCharacter)
			return;

		PlayerCharacter = playerCharacter;
		PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);

		this->SetVisibility(ESlateVisibility::Hidden);
}

void UModelViewerWidget::OnActivate()
{
	this->SetVisibility(ESlateVisibility::Visible);
	// Block movement input
	PlayerController->SetShowMouseCursor(true);
}

void UModelViewerWidget::OnDeactivate()
{
	this->SetVisibility(ESlateVisibility::Hidden);
	PlayerController->SetShowMouseCursor(false);
	PlayerCharacter->IsInViewModel = false;
}
