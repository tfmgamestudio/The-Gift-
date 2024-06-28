// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LightGameInstanceSubsystem.h"
#include "DefaultPointLight.generated.h"

class UPointLightComponent;

UCLASS()
class THEGIFT_API ADefaultPointLight : public AActor
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly)
	USceneComponent* RootCmp = nullptr;

public:
	UPROPERTY(EditDefaultsOnly)
	UPointLightComponent* LightCmp = nullptr;
	// Sets default values for this actor's properties
	ADefaultPointLight();

	UPROPERTY()
	ULightGameInstanceSubsystem* LightSystem = nullptr;

	UPROPERTY()
	bool IsLightOn = true;

	UPROPERTY(EditInstanceOnly)
	bool IsFromMainHallway = false;

	UPROPERTY(EditInstanceOnly)
	bool IsFromBasementHallway = false;

	UPROPERTY(EditInstanceOnly)
	bool IsFromLivingRoom = false;

	UPROPERTY(EditInstanceOnly)
	bool IsFromKitchen = false;

	UPROPERTY(EditInstanceOnly)
	bool IsFromGarage = false;

	UPROPERTY(EditInstanceOnly)
	bool IsFromBathroom = false;

	UPROPERTY(EditInstanceOnly)
	bool IsFromUpstairsHallway = false;

	UPROPERTY(EditInstanceOnly)
	bool IsFromUpstairsKidRoom = false;

	UPROPERTY(EditInstanceOnly)
	bool IsFromUpstairsParentsRoom = false;

	UPROPERTY(EditInstanceOnly)
	bool IsFromUpstairsFinalRoom = false;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
