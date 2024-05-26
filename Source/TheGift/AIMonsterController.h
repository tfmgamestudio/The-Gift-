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
	
	UFUNCTION(BlueprintCallable)
	EPathFollowingRequestResult::Type MoveToEnemy();

	UPROPERTY()
	UBehaviorTreeComponent* BehaviorTreeComponent;

	UPROPERTY(EditAnywhere, Category = "AI")
	UBehaviorTree* BehaviorTree;

	UPROPERTY(BlueprintReadWrite, Category = "AI")
	bool HasSpawned = false;


};
