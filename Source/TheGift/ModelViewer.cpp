// Fill out your copyright notice in the Description page of Project Settings.


#include "ModelViewer.h"

#include "Components/PointLightComponent.h"

// Sets default values
AModelViewer::AModelViewer()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	Root->SetupAttachment(RootComponent);
	SetRootComponent(Root);

	Pivot = CreateDefaultSubobject<USceneComponent>(TEXT("Pivot"));
	Pivot->SetupAttachment(Root);

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	BaseMesh->SetupAttachment(Pivot);

	CaptureComponent2D = CreateDefaultSubobject<USceneCaptureComponent2D>(TEXT("PointLight"));
	CaptureComponent2D->SetupAttachment(Root);

	PointLight1 = CreateDefaultSubobject<UPointLightComponent>(TEXT("PointLightCmp1"));
	PointLight1->SetupAttachment(Root);
	PointLight2 = CreateDefaultSubobject<UPointLightComponent>(TEXT("PointLightCmp2"));
	PointLight2->SetupAttachment(Root);
	PointLight3 = CreateDefaultSubobject<UPointLightComponent>(TEXT("PointLightCmp3"));
	PointLight3->SetupAttachment(Root);
}

void AModelViewer::SetMesh(UStaticMesh* displayMesh)
{
	BaseMesh->SetStaticMesh(displayMesh);
}

void AModelViewer::SetMaterialInstance(UMaterialInterface* displayMaterial)
{
	BaseMesh->SetMaterial(0, displayMaterial);
}

// Called when the game starts or when spawned
void AModelViewer::BeginPlay()
{
	Super::BeginPlay();

	// Sets the actor outside the Skybos so it wont be affected to those lights
	SetActorLocation(OutsideSkyBoxPos, false);
}

// Called every frame
void AModelViewer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	Pivot->SetRelativeRotation(Pivot->GetComponentRotation() + AddRotation, false);
}

