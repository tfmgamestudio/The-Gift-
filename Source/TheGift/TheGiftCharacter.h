// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "TheGiftPlayerController.h"
#include "GameFramework/Character.h"
#include "Logging/LogMacros.h"

#include "TheGiftCharacter.generated.h"

class UMainWidget;
class UInteractRaycast;
class UInputComponent;
class USkeletalMeshComponent;
class UCameraComponent;
class UInputAction;
class UInputMappingContext;
struct FInputActionValue;

DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);

UCLASS(config=Game)
class ATheGiftCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Pawn mesh: 1st person view (arms; seen only by self) */
	UPROPERTY(VisibleDefaultsOnly, Category=Mesh)
	USkeletalMeshComponent* Mesh1P;

	/** First person camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FirstPersonCameraComponent;

	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext;

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputAction* JumpAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputAction* MoveAction;

	/** Interact Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputAction* InteractAction;

	/** Click Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputAction* ClickAction;

	/** Crouch Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputAction* CrouchAction;

	/** Peek Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* PeekRightAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* PeekLeftAction;

public:
	ATheGiftCharacter();

protected:
	virtual void BeginPlay();

	virtual void Tick(float DeltaTime) override;

	// RayCast
	UPROPERTY(EditAnywhere) UInteractRaycast* InteractRaycast = nullptr;
	UPROPERTY() ATheGiftPlayerController* PlayerController = nullptr;;

public:
		
	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* LookAction;

	/** Bool for AnimBP to switch to another animation set */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Weapon)
	bool bHasRifle;

	/** Setter to set the bool */
	UFUNCTION(BlueprintCallable, Category = Weapon)
	void SetHasRifle(bool bNewHasRifle);

	/** Getter for the bool */
	UFUNCTION(BlueprintCallable, Category = Weapon)
	bool GetHasRifle();


	bool LastPeek = false; //Right is true, Left is false
	bool IsPeeking = false;

	float PeekCounter = 0.f;
	/*UPROPERTY(EditDefaultsOnly) float PeekingWalkingSpeed = 0.f;*/

	UPROPERTY(EditDefaultsOnly) float PeekSpeed = 10.f;
	UPROPERTY(EditDefaultsOnly)	FRuntimeFloatCurve AnimationCurve;

	UPROPERTY(EditDefaultsOnly) FVector PeekRightOn = {};
	UPROPERTY(EditDefaultsOnly) FVector PeekLeftOn = {};
	UPROPERTY(EditDefaultsOnly) FVector PeekOff = {};

	UPROPERTY(BlueprintReadWrite) bool IsInViewModel = false;

	UPROPERTY(BlueprintReadWrite) bool IsClicked = false;
	UPROPERTY(BlueprintReadWrite) float RotationSpeed = 2.0f;

protected:
	/** Called for movement input */
	void Move(const FInputActionValue& Value);

	/** Called for looking input */
	void Look(const FInputActionValue& Value);

	/** Called for interact input */
	void Interact();

	/** Called for clicking input */
	void ClickStart();
	void ClickEnd();
	
	/** Called for crouching input */
	void CrouchStart();
	void CrouchEnd();

	/** Called for peeking input */
	void PeekRight();
	void PeekLeft();
	void StopPeek();

protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(UInputComponent* InputComponent) override;
	// End of APawn interface

public:
	/** Returns Mesh1P subobject **/
	USkeletalMeshComponent* GetMesh1P() const { return Mesh1P; }
	/** Returns FirstPersonCameraComponent subobject **/
	UCameraComponent* GetFirstPersonCameraComponent() const { return FirstPersonCameraComponent; }

	UFUNCTION() void SetCurrentInteractingActor(AActor* Interactable)
	{
		InteractingActor = Interactable;
	}
	UFUNCTION() AActor* GetInteractingActor() { return InteractingActor;} 

private:
	UPROPERTY(Transient, SkipSerialization) AActor* InteractingActor = nullptr;
};