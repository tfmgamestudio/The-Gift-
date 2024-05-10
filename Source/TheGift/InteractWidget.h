// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TheGiftCharacter.h"
#include "Blueprint/UserWidget.h"

#include "InteractWidget.generated.h"

/**
 * 
 */
UCLASS()
class THEGIFT_API UInteractWidget : public UUserWidget
{
	GENERATED_BODY()


public:
	void SetUp(ATheGiftCharacter* PlayerCharacter);

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget)) class UTextBlock* InteractText = nullptr;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget)) class UImage* InteractImage = nullptr;

};