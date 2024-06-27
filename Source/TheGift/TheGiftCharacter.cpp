// Copyright Epic Games, Inc. All Rights Reserved.

#include "TheGiftCharacter.h"
#include "Animation/AnimInstance.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "InteractableDoorBase.h"
#include "InteractableInterface.h"
#include "InteractableObjectBase.h"
#include "InteractRaycast.h"
#include "MainWidget.h"
#include "ModelViewer.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "Engine/LocalPlayer.h"
#include "GameFramework/CharacterMovementComponent.h"

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
	CameraRoot = CreateDefaultSubobject<USceneComponent>(TEXT("CameraRoot"));
	CameraRoot->SetupAttachment(GetCapsuleComponent());
	CameraRoot->SetRelativeLocation(FVector(-10.f, 0.f, 60.f)); // Position the camera

	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(CameraRoot);
	//FirstPersonCameraComponent->SetRelativeLocation(FVector(-10.f, 0.f, 60.f)); // Position the camera
	FirstPersonCameraComponent->bUsePawnControlRotation = true;

	// Create a mesh component that will be used when being viewed from a '1st person' view (when controlling this pawn)

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

	IsMoving = GetCharacterMovement()->Velocity.SizeSquared() > 0.0f;

	PeekCounter += DeltaTime;
	CrouchCounter += DeltaTime;
	if (IsPeeking)
	{

		auto value = PeekCounter / ((PeekRightOn - PeekOff).Length() / PeekSpeed);

		const auto eval = PeekAnimCurve.ExternalCurve
			? PeekAnimCurve.ExternalCurve->GetFloatValue(value)
			: PeekAnimCurve.EditorCurveData.Eval(value);

		const auto pos = FMath::Lerp(PeekOff, LastPeek ? PeekRightOn : PeekLeftOn, eval);

		GetFirstPersonCameraComponent()->SetRelativeLocation(pos);
	}
	if (!IsPeeking)
	{

		auto value = PeekCounter / ((GetFirstPersonCameraComponent()->GetRelativeLocation() - PeekOff).Length() / PeekSpeed);

		const auto eval = PeekAnimCurve.ExternalCurve
			? PeekAnimCurve.ExternalCurve->GetFloatValue(value)
			: PeekAnimCurve.EditorCurveData.Eval(value);

		const auto pos = FMath::Lerp(GetFirstPersonCameraComponent()->GetRelativeLocation(), PeekOff, eval);

		GetFirstPersonCameraComponent()->SetRelativeLocation(pos);
	}

	if (IsCrouching)
	{

		auto crouchValue = CrouchCounter / ((CrouchOn - CrouchOff).Length() / CrouchSpeed);

		const auto crouchEval = CrouchAnimCurve.ExternalCurve
			? CrouchAnimCurve.ExternalCurve->GetFloatValue(crouchValue)
			: CrouchAnimCurve.EditorCurveData.Eval(crouchValue);

		auto crouchPos = FMath::Lerp(CrouchOff,CrouchOn, crouchEval);

		GetCharacterMovement()->MaxWalkSpeedCrouched;
		CameraRoot->SetRelativeLocation(crouchPos);
	}
	if (!IsCrouching)
	{

		auto crouchValue = CrouchCounter / ((GetFirstPersonCameraComponent()->GetRelativeLocation() - CrouchOff).Length() / CrouchSpeed);

		const auto crouchEval = CrouchAnimCurve.ExternalCurve
			? CrouchAnimCurve.ExternalCurve->GetFloatValue(crouchValue)
			: CrouchAnimCurve.EditorCurveData.Eval(crouchValue);

		const auto crouchPos = FMath::Lerp(CameraRoot->GetRelativeLocation(), CrouchOff, crouchEval);

		GetCharacterMovement()->MaxWalkSpeed;

		CameraRoot->SetRelativeLocation(crouchPos);
	}

	if(IsInViewModel)
	{
		if(IsClicked)
		{
			float MouseX = 0.0f;
			float MouseY = 0.0f;

			PlayerController->GetInputMouseDelta(MouseX, MouseY);
			//UE_LOGFMT(LogTemp, Log, "Mouse position: {mx}, {my}", ("mx", MouseX), ("my", MouseY));

			Cast<AInteractableObjectBase>(InteractingActor)->ModelViewerActor->Pivot->AddWorldRotation(FRotator(- MouseY * RotationSpeed, - MouseX * RotationSpeed, 0.f));
		}
	}
}

//////////////////////////////////////////////////////////////////////////// Input

void ATheGiftCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		// ClickInteract
		EnhancedInputComponent->BindAction(ClickInteractAction, ETriggerEvent::Started, this, &ATheGiftCharacter::ClickInteract);

		// Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ATheGiftCharacter::Move);

		// Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ATheGiftCharacter::Look);

		// Interacting
		EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Started, this, &ATheGiftCharacter::Interact);

		// Click
		EnhancedInputComponent->BindAction(ClickAction, ETriggerEvent::Started, this, &ATheGiftCharacter::ClickStart);
		EnhancedInputComponent->BindAction(ClickAction, ETriggerEvent::Completed, this, &ATheGiftCharacter::ClickEnd);

		// Crouch
		EnhancedInputComponent->BindAction(CrouchAction, ETriggerEvent::Started, this, &ATheGiftCharacter::CrouchStart);
		EnhancedInputComponent->BindAction(CrouchAction, ETriggerEvent::Completed, this, &ATheGiftCharacter::CrouchEnd);

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
	MovementVector = Value.Get<FVector2D>();
	
	if (Controller != nullptr && !IsInViewModel)
	{
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
			if(!Cast<AInteractableDoorBase>(InteractingActor))
				IInteractableInterface::Execute_Interact(InteractingActor);

			PlayerController->MainWidget->InteractWidget->SetVisibility(ESlateVisibility::Hidden);
		}
	}	
}

void ATheGiftCharacter::ClickStart()
{
	if(IsInViewModel)
	{
		IsClicked = true;
	}
}

void ATheGiftCharacter::ClickEnd()
{
	if(IsInViewModel)
	{
		IsClicked = false;
		// Reset Mouse Position
		PlayerController->SetMouseLocation((PlayerController->MainWidget->GetPaintSpaceGeometry().GetLocalSize().X / 2.0f), (PlayerController->MainWidget->GetPaintSpaceGeometry().GetLocalSize().Y / 2.0f));
	}
}

void ATheGiftCharacter::CrouchStart()
{
	if(CanJump())
	{
		CrouchCounter = 0.f;
		IsCrouching = true;
	}
}

void ATheGiftCharacter::CrouchEnd()
{
	if(CanJump())
	{
		CrouchCounter = 0.f;
		IsCrouching = false;
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

void ATheGiftCharacter::ClickInteract()
{
	UE_LOGFMT(LogTemp, Log, "Open Door Pressed");

	if (InteractingActor)
	{
		if (IInteractableInterface::Execute_CanInteract(InteractingActor))
		{
			if(Cast<AInteractableDoorBase>(InteractingActor))
			{
				IInteractableInterface::Execute_Interact(InteractingActor);

				PlayerController->MainWidget->InteractDoorWidget->SetVisibility(ESlateVisibility::Hidden);

				if(Cast<AInteractableDoorBase>(InteractingActor)->Locked)
				{
					PlayerController->MainWidget->InteractDoorWidget->InteractDoorText->SetOpacity(1.0f);
				}
			}
		}
	}
}

void ATheGiftCharacter::SetHasRifle(bool bNewHasRifle)
{
	bHasRifle = bNewHasRifle;
}

bool ATheGiftCharacter::GetHasRifle()
{
	return bHasRifle;
}

FVector ATheGiftCharacter::GetCharacterVelocity() const
{
	return GetCharacterMovement()->Velocity;
}

FRotator ATheGiftCharacter::GetCharacterDirection() const
{
	if (Controller != nullptr)
	{
		const FRotator Rotation = Controller->GetControlRotation();
		return FRotator(0.0f, Rotation.Yaw, 0.0f);
	}
	return FRotator::ZeroRotator;
}
