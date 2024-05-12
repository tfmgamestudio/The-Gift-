#include "AIMonsterController.h"
#include "BrainComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Waypoint.h"
#include "Runtime/Engine/Public/EngineUtils.h"
#include <Kismet/KismetSystemLibrary.h>
#include <Kismet/GameplayStatics.h>
#include "GameFramework/Character.h"

AAIMonsterController::AAIMonsterController()
{
    BehaviorTreeComponent = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviorTreeComponent"));
}

void AAIMonsterController::BeginPlay()
{
    Super::BeginPlay();

    if (BehaviorTree)
    {
        RunBehaviorTree(BehaviorTree);
        HasSpawned = true;
        GetBlackboardComponent()->SetValueAsBool("HasSpawned", true);
        UE_LOG(LogTemp, Log, TEXT("Behavior tree starting"));

    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("Behavior tree not assigned to AAIMonsterController."));
    }
}

void AAIMonsterController::UpdateNextTargetPoint()
{
    if(HasSpawned)
    {
        UBlackboardComponent* pBlackboardComponent = BrainComponent->GetBlackboardComponent();

        int32 iTargetPointIndex = pBlackboardComponent->GetValueAsInt("TargetPointIndex");

        if (iTargetPointIndex >= 4)
        {
            iTargetPointIndex = 0;
            pBlackboardComponent->SetValueAsInt("TargetPointIndex", iTargetPointIndex);
        }

        for (TActorIterator<AWaypoint> It(GetWorld()); It; ++It)
        {
            AWaypoint* pTargetPoint = *It;

            if (iTargetPointIndex == pTargetPoint->m_iPosition)
            {
                pBlackboardComponent->SetValueAsVector("TargetPointPosition", pTargetPoint->GetActorLocation());
                break;
            }
        }

        pBlackboardComponent->SetValueAsInt("TargetPointIndex", (iTargetPointIndex + 1));   
    }
}

void AAIMonsterController::CheckNearbyEnemy()
{
    if(HasSpawned)
    {
        APawn* pPawn = GetPawn();

        FVector MSStart = pPawn->GetActorLocation();
        FVector MSEnd = MSStart + FVector(0, 0, 15.f);

        TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
        ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECC_Pawn));

        TArray<AActor*> ActorsToIgnore;
        ActorsToIgnore.Add(pPawn);

        TArray<FHitResult> OutHits;

        bool bResult = UKismetSystemLibrary::SphereTraceMultiForObjects(GetWorld(), MSStart, MSEnd, 500.f, ObjectTypes, false, ActorsToIgnore, EDrawDebugTrace::ForDuration, OutHits, true);

        UBlackboardComponent* BlackboardComponent = BrainComponent->GetBlackboardComponent();

        if (bResult)
        {
            for (int32 i = 0; i < OutHits.Num(); i++)
            {
                FHitResult Hit = OutHits[i];

                ACharacter* pCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);

                if (Hit.GetActor() == pCharacter)
                {
                    BlackboardComponent->SetValueAsObject("TargetActorToFollow", pCharacter);
                    MoveToEnemy();
                }
            }
        }
        else
        {
            BlackboardComponent->SetValueAsObject("TargetActorToFollow", nullptr);
        }
    }
}

EPathFollowingRequestResult::Type AAIMonsterController::MoveToEnemy()
{
        UBlackboardComponent* BlackboardComponent = BrainComponent->GetBlackboardComponent();

        AActor* HeroCharacterActor = Cast<AActor>(BlackboardComponent->GetValueAsObject("TargetActorToFollow"));

        EPathFollowingRequestResult::Type MoveToActorResult = MoveToActor(HeroCharacterActor);

        return MoveToActorResult;
}
