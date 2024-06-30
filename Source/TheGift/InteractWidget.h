// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "InteractWidget.generated.h"

class UImage;
class UTextBlock;

UCLASS()
class THEGIFT_API UInteractWidget : public UUserWidget
{
	GENERATED_BODY()


public:
	void SetUp();

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget)) UTextBlock* InteractText = nullptr;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget)) UImage* InteractImage = nullptr;

	UFUNCTION(BlueprintCallable) void OnActivate();
	UFUNCTION(BlueprintCallable) void OnDeactivate();

};