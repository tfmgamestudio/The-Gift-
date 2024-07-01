// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InteractWidget.h"
#include "ModelViewerWidget.h"
#include "Blueprint/UserWidget.h"

#include "MainWidget.generated.h"

/**
 * 
 */
UCLASS()
class THEGIFT_API UMainWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	
	void SetUp();

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget)) UUserWidget* FlashLightWidget = nullptr;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget)) UUserWidget* StaminaBarWidget = nullptr;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget)) UUserWidget* TutorialWidget = nullptr;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget)) UInteractWidget* InteractWidget = nullptr;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget)) UModelViewerWidget* ModelViewerWidget = nullptr;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget)) UUserWidget* ReadableWidget = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite) FText InteractableText;

};
