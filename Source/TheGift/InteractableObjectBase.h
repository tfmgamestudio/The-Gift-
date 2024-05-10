// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InteractableInterface.h"
#include "GameFramework/Actor.h"

#include "InteractableObjectBase.generated.h"

UCLASS()
class THEGIFT_API AInteractableObjectBase : public AActor, public IInteractableInterface
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly) USceneComponent* Root = nullptr;
	UPROPERTY(EditDefaultsOnly) USceneComponent* Pivot = nullptr;
	UPROPERTY(EditAnywhere) UStaticMeshComponent* BaseMesh = nullptr;

public:	
	// Sets default values for this actor's properties
	AInteractableObjectBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
