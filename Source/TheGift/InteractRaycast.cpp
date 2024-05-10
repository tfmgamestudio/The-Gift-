// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractRaycast.h"

#include "InteractableInterface.h"
#include "InteractWidget.h"
#include "Components/SlateWrapperTypes.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"

UInteractRaycast::UInteractRaycast()
{
	PrimaryComponentTick.bCanEverTick = true;
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

		// TODO Send less raycast, not one per tick
		FHitResult HitResult;
		if (UKismetSystemLibrary::LineTraceSingle(World, SpawnLocation, EndLocation, ETraceTypeQuery::TraceTypeQuery1, true, {GetOwner()}, EDrawDebugTrace::None, HitResult, true))
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