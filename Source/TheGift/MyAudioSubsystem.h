// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "MyAudioSubsystem.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, Abstract)
class THEGIFT_API UMyAudioSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

private:
	UPROPERTY()
	float MasterVolume = 1;

	UPROPERTY()
	float MusicVolume = 1;

	UPROPERTY()
	float SFXVolume = 1;

	UPROPERTY()
	float EnvironmentVolume = 1;

	UPROPERTY()
	float VoicesVolume = 1;

public:
	UFUNCTION(BlueprintCallable)
	inline void SetMasterVolume(float volume) { MasterVolume = volume; }

	UFUNCTION(BlueprintCallable)
	inline void SetMusicVolume(float volume) { MusicVolume = volume; }

	UFUNCTION(BlueprintCallable)
	inline void SetSFXVolume(float volume) { SFXVolume = volume; }

	UFUNCTION(BlueprintCallable)
	inline void SetEnvironmentVolume(float volume) { EnvironmentVolume = volume; }

	UFUNCTION(BlueprintCallable)
	inline void SetVoicesVolume(float volume) { VoicesVolume = volume; }


	UFUNCTION(BlueprintCallable)
	inline float GetMasterVolume() { return MasterVolume; }

	UFUNCTION(BlueprintCallable)
	inline float GetMusicVolume() { return MusicVolume; }

	UFUNCTION(BlueprintCallable)
	inline float GetSFXVolume() { return SFXVolume; }

	UFUNCTION(BlueprintCallable)
	inline float GetEnvironmentVolume() { return EnvironmentVolume; }

	UFUNCTION(BlueprintCallable)
	inline float GetVoicesVolume() { return VoicesVolume; }
};
