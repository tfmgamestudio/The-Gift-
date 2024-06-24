#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InteractableInterface.h"
#include "NumberLock.generated.h"

UCLASS()
class THEGIFT_API ANumberLock : public AActor, public IInteractableInterface
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly)
	USceneComponent* RootCmp = nullptr;

	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* MeshCmp = nullptr;

	inline static bool CanInteract = true;

	UPROPERTY()
	int Number = 0;

	UPROPERTY(EditAnywhere)
	int LockPosition = 1; // 1, 2, 3

	inline static int CorrectNumberOne = 2;
	inline static int CorrectNumberTwo = 8;
	inline static int CorrectNumberThree = 7;

	inline static bool IsFirstNumberCorrect = false;
	inline static bool IsSecondNumberCorrect = false;
	inline static bool IsThirdNumberCorrect = false;

	
public:	
	ANumberLock();

	virtual void BeginPlay() override;

	virtual void Interact_Implementation() override;
	virtual bool CanInteract_Implementation() override;

	UFUNCTION()
	void CorrectCombination();

};
