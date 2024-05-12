#include "UpdateNextTargetPointBTTaskNode.h"
#include "AIMonsterController.h"

EBTNodeResult::Type UUpdateNextTargetPointBTTaskNode::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIMonsterController* AIMonsterController = Cast<AAIMonsterController>(OwnerComp.GetOwner());

	AIMonsterController->UpdateNextTargetPoint();

	return EBTNodeResult::Succeeded;
}

FString UUpdateNextTargetPointBTTaskNode::GetStaticDescription() const
{
	return TEXT("Update next point");
}
