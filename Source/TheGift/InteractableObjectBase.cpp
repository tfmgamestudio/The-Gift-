// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractableObjectBase.h"
#include "Logging/StructuredLog.h"

// Sets default values
AInteractableObjectBase::AInteractableObjectBase()
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
void AInteractableObjectBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AInteractableObjectBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AInteractableObjectBase::Interact_Implementation()
{
	IInteractableInterface::Interact_Implementation();

	UE_LOGFMT(LogTemp, Log, "Interacting With Object");

	OnActivate();
}

bool AInteractableObjectBase::CanInteract_Implementation()
{
	return IInteractableInterface::CanInteract_Implementation();

	if (CanInteract)
		return true;
	else
		return false;
}

void AInteractableObjectBase::OnActivate()
{
	CanInteract = false;
}

