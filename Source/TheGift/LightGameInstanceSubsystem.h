// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "LightGameInstanceSubsystem.generated.h"

class ADefaultPointLight;

UCLASS(Blueprintable, Abstract)
class THEGIFT_API ULightGameInstanceSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere)
	TArray<ADefaultPointLight*> LightsArray = {};

	UPROPERTY()
	bool AreLightsOn = true;

	UFUNCTION()
	void TurnOffLights();

	UFUNCTION()
	void TurnOnLights();

	UFUNCTION()
	void SwitchLights();

};
