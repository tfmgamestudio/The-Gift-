#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "AIMonsterController.generated.h"

UCLASS()
class THEGIFT_API AAIMonsterController : public AAIController
{
	GENERATED_BODY()
	
public:

	AAIMonsterController();
	
	void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	void UpdateNextTargetPoint();

	UFUNCTION(BlueprintCallable)
	void CheckNearbyEnemy();
	void ResetShouldLookAround();
	void OnLookAroundTimerComplete();

	UFUNCTION(BlueprintCallable)
	EPathFollowingRequestResult::Type MoveToEnemy();

	UPROPERTY()
	UBehaviorTreeComponent* BehaviorTreeComponent;

	UPROPERTY(EditAnywhere, Category = "AI")
	UBehaviorTree* BehaviorTree;

	UPROPERTY(BlueprintReadWrite, Category = "AI")
	bool HasSpawned = false;

	UPROPERTY(BlueprintReadWrite)
	bool bPlayerFound = false;
	
	UPROPERTY(BlueprintReadWrite)
	bool bPlayerEnteredMultiSphere = false;
	
	UPROPERTY(BlueprintReadWrite)
	bool bPlayerExitedMultiSphere = false;

	FTimerHandle ShouldLookAroundTimerHandle;

	float ShouldLookAroundDuration = 0.f;
};
