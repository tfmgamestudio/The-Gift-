// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InteractableInterface.h"
#include "InteractableDoorBase.h"
#include "Components/TextRenderComponent.h"
#include "TVNumberLock.generated.h"

UCLASS()
class THEGIFT_API ATVNumberLock : public AActor, public IInteractableInterface
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly)
	USceneComponent* RootCmp = nullptr;

	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* MeshCmp = nullptr;

	UPROPERTY(EditDefaultsOnly)
	UTextRenderComponent* NumberText = nullptr;

	UPROPERTY(EditAnywhere)
	AInteractableDoorBase* Door = nullptr;

	UPROPERTY(EditDefaultsOnly)
	USoundBase* CorrectLockSound = nullptr;

	UPROPERTY(EditDefaultsOnly)
	TArray<USoundBase*> LockSounds = {};

	inline static bool CanInteract = true;

	inline static bool HasPlayedSound = false;

	UPROPERTY()
	int Number = 0;

	UPROPERTY(EditAnywhere)
	int LockPosition = 1; // 1, 2, 3, 4

	inline static int CorrectNumberOne = 2;
	inline static int CorrectNumberTwo = 8;
	inline static int CorrectNumberThree = 7;
	inline static int CorrectNumberFour = 6;

	inline static bool IsFirstNumberCorrect = false;
	inline static bool IsSecondNumberCorrect = false;
	inline static bool IsThirdNumberCorrect = false;
	inline static bool IsFourthNumberCorrect = false;


public:
	ATVNumberLock();

	virtual void BeginPlay() override;

	virtual void Interact_Implementation() override;
	virtual bool CanInteract_Implementation() override;

	UFUNCTION()
	void CorrectCombination();

};
