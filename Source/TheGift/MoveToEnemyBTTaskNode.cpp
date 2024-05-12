#include "MoveToEnemyBTTaskNode.h"
#include "AIMonsterController.h"
#include "Navigation/PathFollowingComponent.h"

EBTNodeResult::Type UMoveToEnemyBTTaskNode::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	return EBTNodeResult::InProgress;
}

void UMoveToEnemyBTTaskNode::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	AAIMonsterController* MonsterAIController = Cast<AAIMonsterController>(OwnerComp.GetOwner());

	EPathFollowingRequestResult::Type MoveToActorResult = MonsterAIController->MoveToEnemy();

	if (MoveToActorResult == EPathFollowingRequestResult::AlreadyAtGoal)
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}

}

FString UMoveToEnemyBTTaskNode::GetStaticDescription() const
{
	return TEXT("Following main character");
}
