// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InteractableInterface.h"
#include "TheGiftCharacter.h"
#include "TheGiftPlayerController.h"
#include "GameFramework/Actor.h"

#include "InteractableObjectBase.generated.h"

class AModelViewer;

UCLASS()
class THEGIFT_API AInteractableObjectBase : public AActor, public IInteractableInterface
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly) USceneComponent* Root = nullptr;
	UPROPERTY(EditDefaultsOnly) USceneComponent* Pivot = nullptr;

public:	
	// Sets default values for this actor's properties
	AInteractableObjectBase();

	UPROPERTY(VisibleAnywhere) bool CanInteract = true;
	UPROPERTY(EditAnywhere) bool CanBeInspected = true;

	UPROPERTY(EditAnywhere) UStaticMeshComponent* BaseMesh = nullptr;
	UPROPERTY() UMaterialInterface* BaseMaterial = nullptr;
	UPROPERTY() AModelViewer* ModelViewerActor = nullptr;
	UPROPERTY(EditInstanceOnly) FVector ModelViewerScale = {1.0f, 1.0f, 1.0f};
	UPROPERTY(EditInstanceOnly) FRotator ObjectRotation = { 0.0f, 0.0f, 0.0f};
	UPROPERTY(EditInstanceOnly) FVector ObjectOffset = { 0.0f, 0.0f, 0.0f};

	UPROPERTY(EditAnywhere) bool IsReadable = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) FText InteractableText;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void Interact_Implementation() override;
	virtual bool CanInteract_Implementation() override;

	UFUNCTION() void OnActivate();

private:
	UPROPERTY() ATheGiftPlayerController* PlayerController = nullptr;
	UPROPERTY() ATheGiftCharacter* PlayerCharacter = nullptr;
	
};
