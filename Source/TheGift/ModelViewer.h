// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include <Components/SceneCaptureComponent2D.h>

#include "ModelViewer.generated.h"

class UPointLightComponent;

UCLASS()
class THEGIFT_API AModelViewer : public AActor
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly) USceneComponent* Root = nullptr;
	
	UPROPERTY(EditAnywhere) UStaticMeshComponent* BaseMesh = nullptr;
	UPROPERTY(EditAnywhere) USceneCaptureComponent2D* CaptureComponent2D = nullptr;

	UPROPERTY(EditAnywhere) UPointLightComponent* PointLight1 = nullptr;
	UPROPERTY(EditAnywhere) UPointLightComponent* PointLight2 = nullptr;
	UPROPERTY(EditAnywhere) UPointLightComponent* PointLight3 = nullptr;

	UPROPERTY(EditAnywhere) FVector OutsideSkyBoxPos = {1868660, 0, 0 };
	//{1868660, 0, 0 };
	UPROPERTY(EditAnywhere) FRotator AddRotation = {0.1, 0.0, 0.0};


public:	
	// Sets default values for this actor's properties
	AModelViewer();
	
	void SetMesh(UStaticMesh* displayMesh);
	void SetMaterialInstance(UMaterialInterface* displayMaterial);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditDefaultsOnly) USceneComponent* Pivot = nullptr;
};
