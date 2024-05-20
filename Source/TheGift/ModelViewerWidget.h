// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TheGiftCharacter.h"
#include "TheGiftPlayerController.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/Image.h"

#include "ModelViewerWidget.generated.h"

/**
 * 
 */
UCLASS()
class THEGIFT_API UModelViewerWidget : public UUserWidget
{
	GENERATED_BODY()

	UPROPERTY() ATheGiftCharacter* PlayerCharacter;

	UPROPERTY() ATheGiftPlayerController* PlayerController;

public:
	void SetUp();

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget)) UImage* RenderImage = nullptr;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget)) UButton* BackButton = nullptr;

	void OnActivate();
	void OnDeactivate();
};
