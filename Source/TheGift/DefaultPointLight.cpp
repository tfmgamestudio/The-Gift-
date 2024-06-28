// Fill out your copyright notice in the Description page of Project Settings.


#include "DefaultPointLight.h"

#include "Components/PointLightComponent.h"

// Sets default values
ADefaultPointLight::ADefaultPointLight()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootCmp = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(RootCmp);

	LightCmp = CreateDefaultSubobject<UPointLightComponent>(TEXT("Light"));
	LightCmp->SetupAttachment(RootCmp);
}

// Called when the game starts or when spawned
void ADefaultPointLight::BeginPlay()
{
	Super::BeginPlay();

	LightSystem = GetGameInstance()->GetSubsystem<ULightGameInstanceSubsystem>();

	LightSystem->TotalLightsArray.Add(this);

	if (IsFromMainHallway)
		LightSystem->MainHallwayLightsArray.Add(this);

	if(IsFromBasementHallway)
		LightSystem->BasementHallwayLightsArray.Add(this);

	if (IsFromLivingRoom)
		LightSystem->LivingRoomLightsArray.Add(this);

	if (IsFromKitchen)
		LightSystem->KitchenLightsArray.Add(this);

	if (IsFromGarage)
		LightSystem->GarageLightsArray.Add(this);

	if (IsFromBathroom)
		LightSystem->BathroomLightsArray.Add(this);

	if (IsFromUpstairsHallway)
		LightSystem->UpstairsHallwayLightsArray.Add(this);

	if (IsFromUpstairsKidRoom)
		LightSystem->UpstairsKidRoomLightsArray.Add(this);

	if (IsFromUpstairsParentsRoom)
		LightSystem->UpstairsParentsRoomLightsArray.Add(this);

	if (IsFromUpstairsFinalRoom)
		LightSystem->UpstairsFinalRoomLightsArray.Add(this);
}

// Called every frame
void ADefaultPointLight::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

