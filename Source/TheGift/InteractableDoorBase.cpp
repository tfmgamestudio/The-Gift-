// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractableDoorBase.h"

#include "MainWidget.h"
#include "TheGiftCharacter.h"
#include "TheGiftPlayerController.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"
#include "Logging/StructuredLog.h"

// Sets default values
AInteractableDoorBase::AInteractableDoorBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	Root->SetupAttachment(RootComponent);
	SetRootComponent(Root);

	Pivot = CreateDefaultSubobject<USceneComponent>(TEXT("Pivot"));
	Pivot->SetupAttachment(Root);

	BaseFrame = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Frame"));
	BaseFrame->SetupAttachment(Root);

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	BaseMesh->SetupAttachment(Pivot);
}

// Called when the game starts or when spawned
void AInteractableDoorBase::BeginPlay()
{
	Super::BeginPlay();

	PlayerController = Cast<ATheGiftPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	PlayerCharacter = Cast<ATheGiftCharacter>(PlayerController->GetPawn());
}

// Called every frame
void AInteractableDoorBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AInteractableDoorBase::Interact_Implementation()
{
	IInteractableInterface::Interact_Implementation();

	if(!IsOpen)
		OnActivate();
	else
		OnDeactivate();
}

bool AInteractableDoorBase::CanInteract_Implementation()
{
	if (CanInteract)
		return true;
	else
		return false;
}

void AInteractableDoorBase::OnActivate()
{
	if(!Locked)
	{
		//CanInteract = false;
		IsOpen = true;
		BaseMesh->SetRelativeRotation(FRotator(0.0f, 90.0f, 0.0f));

		if(OpenDoorSound)
			UGameplayStatics::PlaySoundAtLocation(this, OpenDoorSound, GetActorLocation());
	}
	else
	{
		DoorLocked();
	}
}

void AInteractableDoorBase::OnDeactivate()
{
	//CanInteract = true;
	IsOpen = false;
	BaseMesh->SetRelativeRotation(FRotator(0.0f, 0.0f, 0.0f));
	if(CloseDoorSound)
		UGameplayStatics::PlaySoundAtLocation(this, CloseDoorSound, GetActorLocation());
}

void AInteractableDoorBase::DoorLocked()
{
	UE_LOGFMT(LogTemp, Log, "Door Blocked");
	if(LockedDoorSound)
		UGameplayStatics::PlaySoundAtLocation(this, LockedDoorSound, GetActorLocation());
}
