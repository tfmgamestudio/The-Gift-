// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "MyBlueprintSubsystemInitializer.generated.h"

/**
 * 
 */
UCLASS(config = Game, DefaultConfig, meta = (DisplayName = "Blueprint Subsystems"))
class THEGIFT_API UMyBlueprintSubsystemInitializer : public UDeveloperSettings
{
	GENERATED_BODY()

public:
	UPROPERTY(Config, EditAnywhere, Meta = (BlueprintBaseOnly))
	TArray<TSubclassOf<UGameInstanceSubsystem>> GameInstanceSubsystems;
};


UCLASS()
class THEGIFT_API UMyGameInstanceSubsystemInitializer : public UGameInstanceSubsystem
{
	GENERATED_BODY()

	virtual void Initialize(FSubsystemCollectionBase& Collection) override final;
};