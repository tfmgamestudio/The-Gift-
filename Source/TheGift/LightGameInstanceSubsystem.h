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

	UFUNCTION()
	void TurnOffLights(TArray<ADefaultPointLight*> Lights);

	UFUNCTION()
	void TurnOnLights(TArray<ADefaultPointLight*> Lights);

	UFUNCTION()
	void SwitchLights(TArray<ADefaultPointLight*> Lights);

public:
	UPROPERTY(VisibleAnywhere)
	TArray<ADefaultPointLight*> TotalLightsArray = {};

	UPROPERTY(VisibleAnywhere)
	TArray<ADefaultPointLight*> MainHallwayLightsArray = {};

	UPROPERTY(VisibleAnywhere)
	TArray<ADefaultPointLight*> BasementHallwayLightsArray = {};

	UPROPERTY(VisibleAnywhere)
	TArray<ADefaultPointLight*> LivingRoomLightsArray = {};

	UPROPERTY(VisibleAnywhere)
	TArray<ADefaultPointLight*> KitchenLightsArray = {};

	UPROPERTY(VisibleAnywhere)
	TArray<ADefaultPointLight*> GarageLightsArray = {};

	UPROPERTY(VisibleAnywhere)
	TArray<ADefaultPointLight*> BathroomLightsArray = {};

	UPROPERTY(VisibleAnywhere)
	TArray<ADefaultPointLight*> UpstairsHallwayLightsArray = {};

	UPROPERTY(VisibleAnywhere)
	TArray<ADefaultPointLight*> UpstairsKidRoomLightsArray = {};

	UPROPERTY(VisibleAnywhere)
	TArray<ADefaultPointLight*> UpstairsParentsRoomLightsArray = {};

	UPROPERTY(VisibleAnywhere)
	TArray<ADefaultPointLight*> UpstairsFinalRoomLightsArray = {};

	//-----ALL LIGHTS-----
	UFUNCTION()
	void TurnOnAllLights();

	UFUNCTION()
	void TurnOffAllLights();

	UFUNCTION()
	void SwitchAllLights();

	//-----MAIN HALLWAY-----

	void TurnOnMainHallwayLights();

	UFUNCTION()
	void TurnOffMainHallwayLights();

	UFUNCTION()
	void SwitchMainHallwayLights();

	//-----BASEMENT-----

	UFUNCTION()
	void TurnOnBasementHallwayLights();

	UFUNCTION()
	void TurnOffBasementHallwayLights();

	UFUNCTION()
	void SwitchBasementHallwayLights();

	//-----LIVING ROOM-----

	UFUNCTION()
	void TurnOnLivingRoomLights();

	UFUNCTION()
	void TurnOffLivingRoomLights();

	UFUNCTION()
	void SwitchLivingRoomLights();

	//-----KITCHEN-----

	UFUNCTION()
	void TurnOnKitchenLights();

	UFUNCTION()
	void TurnOffKitchenLights();

	UFUNCTION()
	void SwitchKitchenLights();

	//-----GARAGE-----

	UFUNCTION()
	void TurnOnGarageLights();

	UFUNCTION()
	void TurnOffGarageLights();

	UFUNCTION()
	void SwitchGarageLights();

	//-----BATHROOM-----

	UFUNCTION()
	void TurnOnBathroomLights();

	UFUNCTION()
	void TurnOffBathroomLights();

	UFUNCTION()
	void SwitchBathroomLights();

	//-----UPSTAIRS HALLWAY-----

	UFUNCTION()
	void TurnOnUpstairsHallwayLights();

	UFUNCTION()
	void TurnOffUpstairsHallwayLights();

	UFUNCTION()
	void SwitchUpstairsHallwayLights();

	//-----UPSTAIRS KID ROOM-----

	UFUNCTION()
	void TurnOnUpstairsKidRoomLights();

	UFUNCTION()
	void TurnOffUpstairsKidRoomLights();

	UFUNCTION()
	void SwitchUpstairsKidRoomLights();

	//-----UPSTAIRS PARENTS ROOM-----

	UFUNCTION()
	void TurnOnUpstairsParentsRoomLights();

	UFUNCTION()
	void TurnOffUpstairsParentsRoomLights();

	UFUNCTION()
	void SwitchUpstairsParentsRoomLights();

	//-----UPSTAIRS FINAL ROOM-----

	UFUNCTION()
	void TurnOnUpstairsFinalRoomLights();

	UFUNCTION()
	void TurnOffUpstairsFinalRoomLights();

	UFUNCTION()
	void SwitchUpstairsFinalRoomLights();

};
