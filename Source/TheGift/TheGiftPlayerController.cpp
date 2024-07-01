// Copyright Epic Games, Inc. All Rights Reserved.


#include "TheGiftPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "MainWidget.h"

void ATheGiftPlayerController::BeginPlay()
{
	Super::BeginPlay();

	// get the enhanced input subsystem
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		// add the mapping context so we get controls
		Subsystem->AddMappingContext(InputMappingContext, 0);

		//UE_LOG(LogTemp, Warning, TEXT("BeginPlay"));

		if (MainWidgetTemplate)
		{
			MainWidget = CreateWidget<UMainWidget>(this, MainWidgetTemplate);
			MainWidget->AddToViewport();
			MainWidget->SetUp();
		}
	}
}
