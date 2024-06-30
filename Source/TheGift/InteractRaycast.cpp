// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractRaycast.h"

#include "InteractableDoorBase.h"
#include "InteractableInterface.h"
#include "InteractWidget.h"
#include "MainWidget.h"
#include "Components/TextBlock.h"
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
		if(PlayerCharacter == nullptr || PlayerController == nullptr || PlayerCharacter->IsInViewModel)
		{
			return;
		}

		const FVector SpawnLocation = PlayerController->PlayerCameraManager->GetCameraLocation();
		const FVector EndLocation = SpawnLocation + PlayerController->PlayerCameraManager->GetActorForwardVector() * 200.f;

		// TODO Send less raycast, not one per tick
		FHitResult HitResult;
		if (UKismetSystemLibrary::LineTraceSingle(World, SpawnLocation, EndLocation, ETraceTypeQuery::TraceTypeQuery1, true, {GetOwner()}, EDrawDebugTrace::None, HitResult, true))
		{
			if (UKismetSystemLibrary::DoesImplementInterface(HitResult.GetActor(), UInteractableInterface::StaticClass()))
			{				
				if (PlayerCharacter)
				{
					PlayerCharacter->SetCurrentInteractingActor(HitResult.GetActor());

					if (IInteractableInterface::Execute_CanInteract(HitResult.GetActor()))
					{
						if(Cast<AInteractableDoorBase>(HitResult.GetActor()))
						{
							PlayerController->MainWidget->InteractDoorWidget->SetVisibility(ESlateVisibility::Visible);

							// Is Door Locked
							PlayerController->MainWidget->InteractDoorWidget->InteractDoorText->SetOpacity(0.0f);
							if(!Cast<AInteractableDoorBase>(HitResult.GetActor())->Locked)
							{
								PlayerController->MainWidget->InteractDoorWidget->InteractDoorText->SetOpacity(0.0f);
							}
							else
							{
								PlayerController->MainWidget->InteractDoorWidget->InteractDoorText->SetOpacity(1.0f);
							}
						}
						else
						{
							PlayerController->MainWidget->InteractWidget->SetVisibility(ESlateVisibility::Visible);
						}
					}
					else
					{
						if(Cast<AInteractableDoorBase>(HitResult.GetActor()))
							if(Cast<AInteractableDoorBase>(HitResult.GetActor())->IsOpen == true)
								PlayerController->MainWidget->InteractDoorWidget->SetVisibility(ESlateVisibility::Visible);
					}
				}
			}
			else
			{				
				if (PlayerCharacter)
				{
					PlayerCharacter->SetCurrentInteractingActor(nullptr);
					PlayerController->MainWidget->InteractDoorWidget->SetVisibility(ESlateVisibility::Hidden);
					PlayerController->MainWidget->InteractWidget->SetVisibility(ESlateVisibility::Hidden);
				}
			}
		}
		else
		{
			PlayerCharacter->SetCurrentInteractingActor(nullptr);
			PlayerController->MainWidget->InteractDoorWidget->SetVisibility(ESlateVisibility::Hidden);
			PlayerController->MainWidget->InteractWidget->SetVisibility(ESlateVisibility::Hidden);
		}
	}
}
