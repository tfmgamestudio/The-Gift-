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
	UFUNCTION(BlueprintCallable)
	void TurnOnAllLights();

	UFUNCTION(BlueprintCallable)
	void TurnOffAllLights();

	UFUNCTION(BlueprintCallable)
	void SwitchAllLights();

	//-----MAIN HALLWAY-----

	void TurnOnMainHallwayLights();

	UFUNCTION(BlueprintCallable)
	void TurnOffMainHallwayLights();

	UFUNCTION(BlueprintCallable)
	void SwitchMainHallwayLights();

	//-----BASEMENT-----

	UFUNCTION(BlueprintCallable)
	void TurnOnBasementHallwayLights();

	UFUNCTION(BlueprintCallable)
	void TurnOffBasementHallwayLights();

	UFUNCTION(BlueprintCallable)
	void SwitchBasementHallwayLights();

	//-----LIVING ROOM-----

	UFUNCTION(BlueprintCallable)
	void TurnOnLivingRoomLights();

	UFUNCTION(BlueprintCallable)
	void TurnOffLivingRoomLights();

	UFUNCTION(BlueprintCallable)
	void SwitchLivingRoomLights();

	//-----KITCHEN-----

	UFUNCTION(BlueprintCallable)
	void TurnOnKitchenLights();

	UFUNCTION(BlueprintCallable)
	void TurnOffKitchenLights();

	UFUNCTION(BlueprintCallable)
	void SwitchKitchenLights();

	//-----GARAGE-----

	UFUNCTION(BlueprintCallable)
	void TurnOnGarageLights();

	UFUNCTION(BlueprintCallable)
	void TurnOffGarageLights();

	UFUNCTION(BlueprintCallable)
	void SwitchGarageLights();

	//-----BATHROOM-----

	UFUNCTION(BlueprintCallable)
	void TurnOnBathroomLights();

	UFUNCTION(BlueprintCallable)
	void TurnOffBathroomLights();

	UFUNCTION(BlueprintCallable)
	void SwitchBathroomLights();

	//-----UPSTAIRS HALLWAY-----

	UFUNCTION(BlueprintCallable)
	void TurnOnUpstairsHallwayLights();

	UFUNCTION(BlueprintCallable)
	void TurnOffUpstairsHallwayLights();

	UFUNCTION(BlueprintCallable)
	void SwitchUpstairsHallwayLights();

	//-----UPSTAIRS KID ROOM-----

	UFUNCTION(BlueprintCallable)
	void TurnOnUpstairsKidRoomLights();

	UFUNCTION(BlueprintCallable)
	void TurnOffUpstairsKidRoomLights();

	UFUNCTION(BlueprintCallable)
	void SwitchUpstairsKidRoomLights();

	//-----UPSTAIRS PARENTS ROOM-----

	UFUNCTION(BlueprintCallable)
	void TurnOnUpstairsParentsRoomLights();

	UFUNCTION(BlueprintCallable)
	void TurnOffUpstairsParentsRoomLights();

	UFUNCTION(BlueprintCallable)
	void SwitchUpstairsParentsRoomLights();

	//-----UPSTAIRS FINAL ROOM-----

	UFUNCTION(BlueprintCallable)
	void TurnOnUpstairsFinalRoomLights();

	UFUNCTION(BlueprintCallable)
	void TurnOffUpstairsFinalRoomLights();

	UFUNCTION(BlueprintCallable)
	void SwitchUpstairsFinalRoomLights();

};
