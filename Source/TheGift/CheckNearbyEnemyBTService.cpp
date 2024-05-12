#include "CheckNearbyEnemyBTService.h"
#include "BrainComponent.h"
#include "Waypoint.h"
#include "Runtime/Engine/Public/EngineUtils.h"
#include "AIMonsterController.h"

void UCheckNearbyEnemyBTService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	AAIMonsterController* MonsterAIController = Cast<AAIMonsterController>(OwnerComp.GetOwner());

	MonsterAIController->CheckNearbyEnemy();
}
