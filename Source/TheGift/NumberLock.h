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
	UStaticMeshComponent* FirstNumberMesh = nullptr;

	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* SecondNumberMesh = nullptr;

	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* ThirdNumberMesh = nullptr;
	
public:	
	ANumberLock();

	virtual void Interact_Implementation() override;

protected:
	virtual void BeginPlay() override;

};
