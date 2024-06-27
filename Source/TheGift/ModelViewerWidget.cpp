// Fill out your copyright notice in the Description page of Project Settings.


#include "ModelViewerWidget.h"

#include "InteractableObjectBase.h"
#include "MainWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Logging/StructuredLog.h"

void UModelViewerWidget::SetUp()
{		
	PlayerController = Cast<ATheGiftPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	PlayerCharacter = Cast<ATheGiftCharacter>(PlayerController->GetPawn());

	this->SetVisibility(ESlateVisibility::Hidden);
}

void UModelViewerWidget::OnActivate()
{
	this->SetVisibility(ESlateVisibility::Visible);
	// Block movement input
	PlayerController->SetInputMode(FInputModeGameAndUI());
	PlayerController->SetShowMouseCursor(true);
	PlayerController->SetMouseLocation((PlayerController->MainWidget->GetPaintSpaceGeometry().GetLocalSize().X / 2.0f), (PlayerController->MainWidget->GetPaintSpaceGeometry().GetLocalSize().Y / 2.0f));
}

void UModelViewerWidget::OnDeactivate()
{
	this->SetVisibility(ESlateVisibility::Hidden);
	PlayerController->SetInputMode(FInputModeGameOnly());
	PlayerController->SetShowMouseCursor(false);
	PlayerCharacter->IsInViewModel = false;
	Cast<AInteractableObjectBase>(PlayerCharacter->GetInteractingActor())->CanInteract = true;
}
