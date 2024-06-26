// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TheGiftCharacter.h"
#include "TheGiftPlayerController.h"

#include "InteractRaycast.generated.h"

class TheGiftCharacter;
class TheGiftPlayerController;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class THEGIFT_API UInteractRaycast : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInteractRaycast();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(Transient, SkipSerialization) ATheGiftCharacter* PlayerCharacter = nullptr;
	UPROPERTY(Transient, SkipSerialization) ATheGiftPlayerController* PlayerController = nullptr;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION() void InteractRaycast(float DeltaTime);
};