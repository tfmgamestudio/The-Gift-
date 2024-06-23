#include "NumberLock.h"


ANumberLock::ANumberLock()
{
	PrimaryActorTick.bCanEverTick = false;

	RootCmp = CreateDefaultSubobject<USceneComponent>(TEXT("RootCmp"));
	SetRootComponent(RootCmp);

	FirstNumberMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FirstNumberMesh"));
	FirstNumberMesh->SetupAttachment(RootCmp);

	SecondNumberMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SecondNumberMesh"));
	SecondNumberMesh->SetupAttachment(RootCmp);

	ThirdNumberMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ThirdNumberMesh"));
	ThirdNumberMesh->SetupAttachment(RootCmp);

}

void ANumberLock::Interact_Implementation()
{
	IInteractableInterface::Interact_Implementation();

	UE_LOG(LogTemp, Log, TEXT("hola jisjis"));
}

void ANumberLock::BeginPlay()
{
	Super::BeginPlay();
	
}
