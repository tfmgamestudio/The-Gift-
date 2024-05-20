// Copyright Epic Games, Inc. All Rights Reserved.

#include "TheGiftCharacter.h"
#include "Animation/AnimInstance.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "InteractableInterface.h"
#include "InteractableObjectBase.h"
#include "InteractRaycast.h"
#include "MainWidget.h"
#include "Blueprint/UserWidget.h"
#include "Engine/LocalPlayer.h"

#include "Logging/StructuredLog.h"

DEFINE_LOG_CATEGORY(LogTemplateCharacter);

//////////////////////////////////////////////////////////////////////////
// ATheGiftCharacter

ATheGiftCharacter::ATheGiftCharacter()
{
	// Character doesnt have a rifle at start
	bHasRifle = false;
	
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);
		
	// Create a CameraComponent	
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	FirstPersonCameraComponent->SetRelativeLocation(FVector(-10.f, 0.f, 60.f)); // Position the camera
	FirstPersonCameraComponent->bUsePawnControlRotation = true;

	// Create a mesh component that will be used when being viewed from a '1st person' view (when controlling this pawn)
	Mesh1P = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh1P"));
	Mesh1P->SetOnlyOwnerSee(true);
	Mesh1P->SetupAttachment(FirstPersonCameraComponent);
	Mesh1P->bCastDynamicShadow = false;
	Mesh1P->CastShadow = false;
	//Mesh1P->SetRelativeRotation(FRotator(0.9f, -19.19f, 5.2f));
	Mesh1P->SetRelativeLocation(FVector(-30.f, 0.f, -150.f));

	// RayCast
	InteractRaycast = CreateDefaultSubobject<UInteractRaycast>(TEXT("InteractRayCast"));
}

void ATheGiftCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	// Add Input Mapping Context
	PlayerController = Cast<ATheGiftPlayerController>(Controller);
	
	if (PlayerController)
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
}

void ATheGiftCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	PeekCounter += DeltaTime;
	if (IsPeeking)
	{

		auto value = PeekCounter / ((PeekRightOn - PeekOff).Length() / PeekSpeed);

		const auto eval = AnimationCurve.ExternalCurve
			? AnimationCurve.ExternalCurve->GetFloatValue(value)
			: AnimationCurve.EditorCurveData.Eval(value);

		const auto pos = FMath::Lerp(PeekOff, LastPeek ? PeekRightOn : PeekLeftOn, eval);

		GetFirstPersonCameraComponent()->SetRelativeLocation(pos);
		/*GetCharacterMovement()->MaxWalkSpeed = PeekingWalkingSpeed;*/
	}
	if (!IsPeeking)
	{

		auto value = PeekCounter / ((GetFirstPersonCameraComponent()->GetRelativeLocation() - PeekOff).Length() / PeekSpeed);

		const auto eval = AnimationCurve.ExternalCurve
			? AnimationCurve.ExternalCurve->GetFloatValue(value)
			: AnimationCurve.EditorCurveData.Eval(value);

		const auto pos = FMath::Lerp(GetFirstPersonCameraComponent()->GetRelativeLocation(), PeekOff, eval);

		GetFirstPersonCameraComponent()->SetRelativeLocation(pos);
		/*GetCharacterMovement()->MaxWalkSpeed = 600.f;*/
	}

	if(IsInViewModel)
	{
		float MouseX = 0.0f;
		float MouseY = 0.0f;

		PlayerController->GetInputMouseDelta(MouseX, MouseY);

		UE_LOGFMT(LogTemp, Log, "Mouse position: {mx}, {my}", ("mx", MouseX), ("my", MouseY));
		
	}
}

//////////////////////////////////////////////////////////////////////////// Input

void ATheGiftCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		// Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		// Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ATheGiftCharacter::Move);

		// Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ATheGiftCharacter::Look);

		// Interacting
		EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Triggered, this, &ATheGiftCharacter::Interact);

		// Click
		EnhancedInputComponent->BindAction(ClickAction, ETriggerEvent::Triggered, this, &ATheGiftCharacter::Click);

		// Peeking
		EnhancedInputComponent->BindAction(PeekRightAction, ETriggerEvent::Started, this, &ATheGiftCharacter::PeekRight);
		EnhancedInputComponent->BindAction(PeekRightAction, ETriggerEvent::Completed, this, &ATheGiftCharacter::StopPeek);

		EnhancedInputComponent->BindAction(PeekLeftAction, ETriggerEvent::Started, this, &ATheGiftCharacter::PeekLeft);
		EnhancedInputComponent->BindAction(PeekLeftAction, ETriggerEvent::Completed, this, &ATheGiftCharacter::StopPeek);
	}
	else
	{
		UE_LOG(LogTemplateCharacter, Error, TEXT("'%s' Failed to find an Enhanced Input Component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}

void ATheGiftCharacter::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr && !IsInViewModel)
	{
		// add movement 
		AddMovementInput(GetActorForwardVector(), MovementVector.Y);
		AddMovementInput(GetActorRightVector(), MovementVector.X);
	}
}

void ATheGiftCharacter::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr && !IsInViewModel)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void ATheGiftCharacter::Interact()
{
	UE_LOGFMT(LogTemp, Log, "InteractPressed");

	if (InteractingActor)
	{
		if (IInteractableInterface::Execute_CanInteract(InteractingActor))
		{
			IInteractableInterface::Execute_Interact(InteractingActor);

			PlayerController->MainWidget->InteractWidget->SetVisibility(ESlateVisibility::Hidden);
		}
		else
		{

		}
	}	
}

void ATheGiftCharacter::Click()
{
	if(IsInViewModel)
	{
		
	}
}

void ATheGiftCharacter::PeekRight()
{
	PeekCounter = 0.f;
	LastPeek = true;
	IsPeeking = true;
}


void ATheGiftCharacter::PeekLeft()
{
	PeekCounter = 0.f;
	LastPeek = false;
	IsPeeking = true;
}

void ATheGiftCharacter::StopPeek()
{
	PeekCounter = 0.f;
	IsPeeking = false;
}

void ATheGiftCharacter::SetHasRifle(bool bNewHasRifle)
{
	bHasRifle = bNewHasRifle;
}

bool ATheGiftCharacter::GetHasRifle()
{
	return bHasRifle;
}