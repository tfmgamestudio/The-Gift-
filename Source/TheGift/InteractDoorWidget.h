// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "InteractDoorWidget.generated.h"

class UImage;
class UTextBlock;
/**
 * 
 */
UCLASS()
class THEGIFT_API UInteractDoorWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void SetUp();

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget)) UTextBlock* InteractDoorText = nullptr;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget)) UTextBlock* InteractDoorClickText = nullptr;
};
