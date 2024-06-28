// Fill out your copyright notice in the Description page of Project Settings.


#include "LightGameInstanceSubsystem.h"

#include "DefaultPointLight.h"
#include "Components/PointLightComponent.h"

void ULightGameInstanceSubsystem::TurnOffLights(TArray<ADefaultPointLight*> Lights)
{
	for (ADefaultPointLight* light : Lights)
	{
		if (light)
		{
			light->LightCmp->SetHiddenInGame(true);
			light->IsLightOn = false;
		}
	}
}

void ULightGameInstanceSubsystem::TurnOnLights(TArray<ADefaultPointLight*> Lights)
{
	for (ADefaultPointLight* light : Lights)
	{
		if (light)
		{
			light->LightCmp->SetHiddenInGame(false);
			light->IsLightOn = true;
		}
	}
}

void ULightGameInstanceSubsystem::SwitchLights(TArray<ADefaultPointLight*> Lights)
{
	for (ADefaultPointLight* light : Lights)
	{
		if (light)
		{
			if(light->IsLightOn)
			{
				light->LightCmp->SetHiddenInGame(true);
				light->IsLightOn = false;
			}
				
			else
			{
				light->LightCmp->SetHiddenInGame(false);
				light->IsLightOn = true;
			}
		}
	}
}

//-----ALL LIGHTS-----

void ULightGameInstanceSubsystem::TurnOnAllLights()
{
	TurnOnLights(TotalLightsArray);
}

void ULightGameInstanceSubsystem::TurnOffAllLights()
{
	TurnOffLights(TotalLightsArray);
}

void ULightGameInstanceSubsystem::SwitchAllLights()
{
	SwitchLights(TotalLightsArray);
}

//-----MAIN HALLWAY-----

void ULightGameInstanceSubsystem::TurnOnMainHallwayLights()
{
	TurnOnLights(MainHallwayLightsArray);
}

void ULightGameInstanceSubsystem::TurnOffMainHallwayLights()
{
	TurnOffLights(MainHallwayLightsArray);
}

void ULightGameInstanceSubsystem::SwitchMainHallwayLights()
{
	SwitchLights(MainHallwayLightsArray);
}

//-----BASEMENT-----

void ULightGameInstanceSubsystem::TurnOnBasementHallwayLights()
{
	TurnOnLights(BasementHallwayLightsArray);
}

void ULightGameInstanceSubsystem::TurnOffBasementHallwayLights()
{
	TurnOffLights(BasementHallwayLightsArray);
}

void ULightGameInstanceSubsystem::SwitchBasementHallwayLights()
{
	SwitchLights(BasementHallwayLightsArray);
}

//-----LIVING ROOM-----

void ULightGameInstanceSubsystem::TurnOnLivingRoomLights()
{
	TurnOnLights(LivingRoomLightsArray);
}

void ULightGameInstanceSubsystem::TurnOffLivingRoomLights()
{
	TurnOffLights(LivingRoomLightsArray);
}

void ULightGameInstanceSubsystem::SwitchLivingRoomLights()
{
	SwitchLights(LivingRoomLightsArray);
}

//-----KITCHEN-----

void ULightGameInstanceSubsystem::TurnOnKitchenLights()
{
	TurnOnLights(KitchenLightsArray);
}

void ULightGameInstanceSubsystem::TurnOffKitchenLights()
{
	TurnOffLights(KitchenLightsArray);
}

void ULightGameInstanceSubsystem::SwitchKitchenLights()
{
	SwitchLights(KitchenLightsArray);
}

//-----GARAGE-----

void ULightGameInstanceSubsystem::TurnOnGarageLights()
{
	TurnOnLights(GarageLightsArray);
}

void ULightGameInstanceSubsystem::TurnOffGarageLights()
{
	TurnOffLights(GarageLightsArray);
}

void ULightGameInstanceSubsystem::SwitchGarageLights()
{
	SwitchLights(GarageLightsArray);
}

//-----BATHROOM-----

void ULightGameInstanceSubsystem::TurnOnBathroomLights()
{
	TurnOnLights(BathroomLightsArray);
}

void ULightGameInstanceSubsystem::TurnOffBathroomLights()
{
	TurnOffLights(BathroomLightsArray);
}

void ULightGameInstanceSubsystem::SwitchBathroomLights()
{
	SwitchLights(BathroomLightsArray);
}

//-----UPSTAIRS HALLWAY-----

void ULightGameInstanceSubsystem::TurnOnUpstairsHallwayLights()
{
	TurnOnLights(UpstairsHallwayLightsArray);
}

void ULightGameInstanceSubsystem::TurnOffUpstairsHallwayLights()
{
	TurnOffLights(UpstairsHallwayLightsArray);
}

void ULightGameInstanceSubsystem::SwitchUpstairsHallwayLights()
{
	SwitchLights(UpstairsHallwayLightsArray);
}

//-----UPSTAIRS KID ROOM-----

void ULightGameInstanceSubsystem::TurnOnUpstairsKidRoomLights()
{
	TurnOnLights(UpstairsKidRoomLightsArray);
}

void ULightGameInstanceSubsystem::TurnOffUpstairsKidRoomLights()
{
	TurnOffLights(UpstairsKidRoomLightsArray);
}

void ULightGameInstanceSubsystem::SwitchUpstairsKidRoomLights()
{
	SwitchLights(UpstairsKidRoomLightsArray);
}

//-----UPSTAIRS PARENTS ROOM-----

void ULightGameInstanceSubsystem::TurnOnUpstairsParentsRoomLights()
{
	TurnOnLights(UpstairsParentsRoomLightsArray);
}

void ULightGameInstanceSubsystem::TurnOffUpstairsParentsRoomLights()
{
	TurnOffLights(UpstairsParentsRoomLightsArray);
}

void ULightGameInstanceSubsystem::SwitchUpstairsParentsRoomLights()
{
	SwitchLights(UpstairsParentsRoomLightsArray);
}

//-----UPSTAIRS FINAL ROOM-----

void ULightGameInstanceSubsystem::TurnOnUpstairsFinalRoomLights()
{
	TurnOnLights(UpstairsFinalRoomLightsArray);
}

void ULightGameInstanceSubsystem::TurnOffUpstairsFinalRoomLights()
{
	TurnOffLights(UpstairsFinalRoomLightsArray);
}

void ULightGameInstanceSubsystem::SwitchUpstairsFinalRoomLights()
{
	SwitchLights(UpstairsFinalRoomLightsArray);
}
