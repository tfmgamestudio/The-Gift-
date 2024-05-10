// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractRaycast.h"

#include "InteractableInterface.h"
#include "InteractWidget.h"
#include "Camera/CameraComponent.h"
#include "Components/SlateWrapperTypes.h"
#include "GameFramework/DefaultPhysicsVolume.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"

// Sets default values for this component's properties
UInteractRaycast::UInteractRaycast()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UInteractRaycast::BeginPlay()
{
	Super::BeginPlay();

	PlayerCharacter = Cast<ATheGiftCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	PlayerController = Cast<ATheGiftPlayerController>(PlayerCharacter->GetController());
}


// Called every frame
void UInteractRaycast::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	InteractRaycast(DeltaTime);
}

void UInteractRaycast::InteractRaycast(float DeltaTime)
{
	UWorld* const World = GetWorld();

	if (World != nullptr)
	{
		if (PlayerCharacter == nullptr || PlayerController == nullptr)
		{
			return;
		}

		const FVector SpawnLocation = PlayerController->PlayerCameraManager->GetCameraLocation();
		const FVector EndLocation = SpawnLocation + PlayerController->PlayerCameraManager->GetActorForwardVector() * 10000.f;

		FHitResult HitResult;

		// TODO Send less raycast, not one per tick
		if (UKismetSystemLibrary::LineTraceSingle(World, SpawnLocation, EndLocation, ETraceTypeQuery::TraceTypeQuery1, true, {GetOwner()}, EDrawDebugTrace::N, HitResult, true))
		{
			if (UKismetSystemLibrary::DoesImplementInterface(HitResult.GetActor(), UInteractableInterface::StaticClass()))
			{				
				if (PlayerCharacter)
				{
					PlayerCharacter->SetCurrentInteractingActor(HitResult.GetActor());
					// TODO Just for testing without input
					PlayerCharacter->InteractWidget->SetVisibility(ESlateVisibility::Visible);

					if (IInteractableInterface::Execute_CanInteract(HitResult.GetActor()))
					{
						PlayerCharacter->InteractWidget->SetVisibility(ESlateVisibility::Visible);
					}
				}
			}
			else
			{				
				if (PlayerCharacter)
				{
					PlayerCharacter->SetCurrentInteractingActor(nullptr);
					PlayerCharacter->InteractWidget->SetVisibility(ESlateVisibility::Hidden);
				}
			}
		}
		else
		{
			PlayerCharacter->SetCurrentInteractingActor(nullptr);
			PlayerCharacter->InteractWidget->SetVisibility(ESlateVisibility::Hidden);
		}
	}
}