// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TheGiftPlayerController.generated.h"

class UMainWidget;
class UInputMappingContext;

/**
 *
 */
UCLASS()
class THEGIFT_API ATheGiftPlayerController : public APlayerController
{
	GENERATED_BODY()
	
protected:

	/** Input Mapping Context to be used for player input */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputMappingContext* InputMappingContext;

	// Begin Actor interface
protected:

	virtual void BeginPlay() override;

	// End Actor interface

public:
	// Main Widget
	UPROPERTY(EditDefaultsOnly) TSubclassOf<UMainWidget> MainWidgetTemplate = nullptr;
	UPROPERTY() UMainWidget* MainWidget = nullptr;
};
