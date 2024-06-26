// Fill out your copyright notice in the Description page of Project Settings.


#include "LightGameInstanceSubsystem.h"

#include "DefaultPointLight.h"
#include "Components/PointLightComponent.h"

void ULightGameInstanceSubsystem::TurnOffLights()
{
	for (ADefaultPointLight* light : LightsArray)
	{
		if (light)
		{
			light->LightCmp->SetHiddenInGame(true);
			AreLightsOn = false;
		}
	}
}

void ULightGameInstanceSubsystem::TurnOnLights()
{
	for (ADefaultPointLight* light : LightsArray)
	{
		if (light)
		{
			light->LightCmp->SetHiddenInGame(false);
			AreLightsOn = true;

		}
	}
}

void ULightGameInstanceSubsystem::SwitchLights()
{
	for (ADefaultPointLight* light : LightsArray)
	{
		if (light)
		{
			if(AreLightsOn)
			{
				light->LightCmp->SetHiddenInGame(true);
			}
				
			else
			{
				light->LightCmp->SetHiddenInGame(false);
			}
		}
	}
	AreLightsOn = !AreLightsOn;
}
