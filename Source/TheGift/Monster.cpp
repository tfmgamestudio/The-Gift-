#include "Monster.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "AIMonsterController.h"

AMonster::AMonster()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AMonster::BeginPlay()
{
	Super::BeginPlay();
}

void AMonster::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AMonster::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void AMonster::Move(const FVector2D& Value)
{
	MovementVector = Value;

	AAIMonsterController* AIController = Cast<AAIMonsterController>(GetController());
	if (AIController != nullptr)
	{
		const FRotator Rotation = AIController->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
	}
}

FVector AMonster::GetCharacterVelocity() const
{
	return GetCharacterMovement()->Velocity;
}

FRotator AMonster::GetCharacterDirection() const
{
	AAIMonsterController* AIController = Cast<AAIMonsterController>(GetController());
	if (AIController != nullptr)
	{
		const FRotator Rotation = AIController->GetControlRotation();
		return FRotator(0.0f, Rotation.Yaw, 0.0f);
	}
	return FRotator::ZeroRotator;
}
