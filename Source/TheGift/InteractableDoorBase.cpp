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

	if (IsMoving)
	{
		Counter += DeltaTime;

		const auto Value = Counter / DoorTimeAnim;

		const auto Eval = AnimationCurve.ExternalCurve
			? AnimationCurve.ExternalCurve->GetFloatValue(Value)
			: AnimationCurve.EditorCurveData.Eval(Value);

		const auto Rot = FMath::Lerp(InitialRotationDegrees, FinalRotationDegrees , Eval);

		BaseMesh->SetRelativeRotation(FRotator(0.0f, Rot, 0.0f));

		if(Counter >= DoorTimeAnim)
			AnimEnded();
	}
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
		CanInteract = false;
		IsOpen = true;
		IsMoving = true;

		InitialRotationDegrees = CloseRotationDegrees;
		FinalRotationDegrees = OpenRotationDegrees;

		if(OpenDoorSound)
		{
			UGameplayStatics::PlaySoundAtLocation(this, OpenDoorSound, GetActorLocation());
			if(!DoOnce && PlaysCreepySound)
			{
				DoOnce = true;
				UGameplayStatics::PlaySoundAtLocation(this, CreepyOpenDoorSound, GetActorLocation());
			}
		}
			
	}
	else
	{
		DoorLocked();
	}
}

void AInteractableDoorBase::OnDeactivate()
{
	CanInteract = false;
	IsOpen = false;
	IsMoving = true;

	InitialRotationDegrees = OpenRotationDegrees;
	FinalRotationDegrees = CloseRotationDegrees;

	if(CloseDoorSound)
		UGameplayStatics::PlaySoundAtLocation(this, CloseDoorSound, GetActorLocation());
}

void AInteractableDoorBase::DoorLocked()
{
	if(LockedDoorSound)
		UGameplayStatics::PlaySoundAtLocation(this, LockedDoorSound, GetActorLocation());
}

void AInteractableDoorBase::AnimEnded()
{
	Counter = 0.0f;
	IsMoving = false;
	CanInteract = true;
}
