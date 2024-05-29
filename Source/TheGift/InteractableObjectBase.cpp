// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractableObjectBase.h"

#include "MainWidget.h"
#include "ModelViewer.h"
#include "Kismet/GameplayStatics.h"
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

	PlayerController = Cast<ATheGiftPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	PlayerCharacter = Cast<ATheGiftCharacter>(PlayerController->GetPawn());

	BaseMaterial = BaseMesh->GetMaterial(0);
}

// Called every frame
void AInteractableObjectBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AInteractableObjectBase::Interact_Implementation()
{
	IInteractableInterface::Interact_Implementation();

	OnActivate();
}

bool AInteractableObjectBase::CanInteract_Implementation()
{
	if (CanInteract)
		return true;
	else
		return false;
}

void AInteractableObjectBase::OnActivate()
{
	CanInteract = false;
	UE_LOGFMT(LogTemp, Log, "Interacting With Object");

	if(CanBeInspected)
	{
		// TODO Guardar en un puntero statico
		TArray<AActor*> FoundActors;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), AModelViewer::StaticClass(), FoundActors);

		for(auto* actor : FoundActors)
		{
			if(auto* foundActor = Cast<AModelViewer>(actor))	
			{
				ModelViewerActor = foundActor;
				ModelViewerActor->SetMesh(BaseMesh->GetStaticMesh());
				ModelViewerActor->SetMaterialInstance(BaseMaterial);
				ModelViewerActor->SetScale(ModelViewerScale);
				ModelViewerActor->Pivot->SetRelativeRotation(FRotator(0.0f, 0.0f, 0.0f));
			}
		}
		PlayerCharacter->IsInViewModel = true;
		PlayerController->MainWidget->ModelViewerWidget->OnActivate();
	}
}
