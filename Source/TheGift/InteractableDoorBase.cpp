// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractableDoorBase.h"

#include "TheGiftCharacter.h"
#include "TheGiftPlayerController.h"
#include "Kismet/GameplayStatics.h"

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

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	BaseMesh->SetupAttachment(Root);
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
	CanInteract = false;

}
