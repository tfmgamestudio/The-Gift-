#include "NumberLock.h"

#include "Logging/StructuredLog.h"


ANumberLock::ANumberLock()
{
	PrimaryActorTick.bCanEverTick = false;

	RootCmp = CreateDefaultSubobject<USceneComponent>(TEXT("RootCmp"));
	SetRootComponent(RootCmp);

	MeshCmp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	MeshCmp->SetupAttachment(RootCmp);

}

void ANumberLock::BeginPlay()
{
	Super::BeginPlay();

	IsFirstNumberCorrect = false;
	IsSecondNumberCorrect = false;
	IsThirdNumberCorrect = false;
	IsFourthNumberCorrect = false;
	CanInteract = true;
}

void ANumberLock::Interact_Implementation()
{
	IInteractableInterface::Interact_Implementation();

	MeshCmp->AddLocalRotation({ 0, 36, 0 });

	Number += 1;
	if (Number == 10)
		Number = 0;

	if (LockPosition == 1)
		if (Number == CorrectNumberOne)
			IsFirstNumberCorrect = true;
		else
			IsFirstNumberCorrect = false;

	else if (LockPosition == 2)
		if (Number == CorrectNumberTwo)
			IsSecondNumberCorrect = true;
		else
			IsSecondNumberCorrect = false;

	else if (LockPosition == 3)
		if (Number == CorrectNumberThree)
			IsThirdNumberCorrect = true;
		else
			IsThirdNumberCorrect = false;

	else if (LockPosition == 4)
		if (Number == CorrectNumberFour)
			IsFourthNumberCorrect = true;
		else
			IsFourthNumberCorrect = false;

	UE_LOGFMT(LogTemp, Log, "Number is: {0}", Number);

	if (IsFirstNumberCorrect && IsSecondNumberCorrect && IsThirdNumberCorrect && IsFourthNumberCorrect)
		CorrectCombination();
}

bool ANumberLock::CanInteract_Implementation()
{
	if (CanInteract)
		return true;
	else
		return false;
}

void ANumberLock::CorrectCombination()
{
	UE_LOG(LogTemp, Log, TEXT("Lock Open"));
	CanInteract = false;
	Door->Locked = false;
}