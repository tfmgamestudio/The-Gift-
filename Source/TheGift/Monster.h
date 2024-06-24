#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Monster.generated.h"

UCLASS()
class THEGIFT_API AMonster : public ACharacter
{
	GENERATED_BODY()

public:
	AMonster();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(BlueprintReadWrite)
	FVector2D MovementVector{0, 0};
	
	UPROPERTY(BlueprintReadWrite)
	FVector2D RotationVector{0, 0};

	UFUNCTION(BlueprintCallable)
	void Move(const FVector2D& Value);

	UFUNCTION(BlueprintPure)
	FVector GetCharacterVelocity() const;

	UFUNCTION(BlueprintPure)
	FRotator GetCharacterDirection() const;
};
