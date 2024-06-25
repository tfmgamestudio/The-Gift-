// Fill out your copyright notice in the Description page of Project Settings.


#include "MyBlueprintSubsystemInitializer.h"

void UMyGameInstanceSubsystemInitializer::Initialize(FSubsystemCollectionBase& Collection)
{
	const UMyBlueprintSubsystemInitializer* BlueprintSubsystemInitializer = GetDefault<UMyBlueprintSubsystemInitializer>();

	if(BlueprintSubsystemInitializer->GameInstanceSubsystems.IsEmpty())
	{
		UE_LOG(LogTemp, Error, TEXT("UMyGameInstanceSubsystemInitializer::Initialize  -  Empty GameInstanceSubsystems array"))
			return;
	}

	for(TSubclassOf<UGameInstanceSubsystem> Subsystem : BlueprintSubsystemInitializer->GameInstanceSubsystems)
	{
		Collection.InitializeDependency(Subsystem);
	}
}
