#include "TVNumberLock.h"

#include "Kismet/GameplayStatics.h"
#include "Logging/StructuredLog.h"

// Sets default values
ATVNumberLock::ATVNumberLock()
{
	PrimaryActorTick.bCanEverTick = false;

	PrimaryActorTick.bCanEverTick = false;

	RootCmp = CreateDefaultSubobject<USceneComponent>(TEXT("RootCmp"));
	SetRootComponent(RootCmp);

	MeshCmp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	MeshCmp->SetupAttachment(RootCmp);

	NumberText = CreateDefaultSubobject<UTextRenderComponent>(TEXT("Number"));
	NumberText->SetupAttachment(RootCmp);
}

void ATVNumberLock::BeginPlay()
{
	Super::BeginPlay();

	NumberText->SetText(FText::FromString(FString::FromInt(Number)));
	HasPlayedSound = false;
	IsFirstNumberCorrect = false;
	IsSecondNumberCorrect = false;
	IsThirdNumberCorrect = false;
	IsFourthNumberCorrect = false;
	CanInteract = true;
}

void ATVNumberLock::Interact_Implementation()
{
	IInteractableInterface::Interact_Implementation();
	if (LockSounds.Num() > 0)
	{
		int32 RandomIndex = FMath::RandRange(0, LockSounds.Num() - 1);

		USoundBase* RandomSound = LockSounds[RandomIndex];

		UGameplayStatics::PlaySoundAtLocation(this, RandomSound, GetActorLocation());
	}

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

	NumberText->SetText(FText::FromString(FString::FromInt(Number)));

	UE_LOGFMT(LogTemp, Log, "Number is: {0}", Number);

	if (IsFirstNumberCorrect && IsSecondNumberCorrect && IsThirdNumberCorrect && IsFourthNumberCorrect)
		CorrectCombination();
}

bool ATVNumberLock::CanInteract_Implementation()
{
	if (CanInteract)
		return true;
	else
		return false;
}

void ATVNumberLock::CorrectCombination()
{
	UE_LOG(LogTemp, Log, TEXT("Lock Open"));
	CanInteract = false;
	if (Door)
		Door->Locked = false;

	if (!HasPlayedSound && CorrectLockSound)
	{
		UGameplayStatics::PlaySoundAtLocation(this, CorrectLockSound, GetActorLocation());
		HasPlayedSound = true;
	}
}