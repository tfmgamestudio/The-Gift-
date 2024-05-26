#include "AIMonsterController.h"
#include "BrainComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Waypoint.h"
#include "Runtime/Engine/Public/EngineUtils.h"
#include <Kismet/KismetSystemLibrary.h>
#include <Kismet/GameplayStatics.h>

#include "Components/CapsuleComponent.h"
#include "GameFramework/Character.h"
#include "Navigation/PathFollowingComponent.h"

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
    if (HasSpawned)
    {
        APawn* AIPawn = GetPawn();
        ACharacter* PlayerCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
        
        FVector SphereCastStart = AIPawn->GetActorLocation();
        FVector SphereCastEnd = SphereCastStart + FVector(0, 0, 15.f); // Adjust as needed

        // Perform sphere cast to detect nearby enemies
        TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
        ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECC_Pawn));

        TArray<AActor*> ActorsToIgnore;
        ActorsToIgnore.Add(AIPawn);

        TArray<FHitResult> SphereCastHits;

        bool bSphereCastResult = UKismetSystemLibrary::SphereTraceMultiForObjects(GetWorld(), SphereCastStart, SphereCastEnd, 1000.f, ObjectTypes, false, ActorsToIgnore, EDrawDebugTrace::ForDuration, SphereCastHits, true);

        UBlackboardComponent* BlackboardComponent = BrainComponent->GetBlackboardComponent();

        if (bSphereCastResult)
        {
            for (const FHitResult& SphereCastHit : SphereCastHits)
            {
                if (SphereCastHit.GetActor() == PlayerCharacter)
                {
                    FVector LineTraceStart = AIPawn->GetActorLocation();
                    FVector LineTraceEnd = PlayerCharacter->GetCapsuleComponent()->GetComponentLocation();

                    FHitResult LineTraceHit;
                    FCollisionQueryParams CollisionParams;
                    CollisionParams.AddIgnoredActor(AIPawn);

                    bool bLineTraceResult = GetWorld()->LineTraceSingleByChannel(LineTraceHit, LineTraceStart, LineTraceEnd, ECC_Pawn, CollisionParams);

                    if (bLineTraceResult && LineTraceHit.GetActor() == PlayerCharacter)
                    {
                        BlackboardComponent->SetValueAsObject("TargetActorToFollow", PlayerCharacter);
                        UE_LOG(LogTemp, Log, TEXT("Player detected and visible, moving to enemy."));
                        MoveToEnemy();
                        return; 
                    }
                    else
                    {
                        // Player not hit by line trace
                        BlackboardComponent->SetValueAsObject("TargetActorToFollow", nullptr);
                        UE_LOG(LogTemp, Log, TEXT("Player detected and not visible."));
                        break;
                    }
                }
            }
        }

        // No player detected or not visible
        BlackboardComponent->SetValueAsObject("TargetActorToFollow", nullptr);
        UE_LOG(LogTemp, Log, TEXT("No nearby enemies detected or player not visible."));
    }
}


EPathFollowingRequestResult::Type AAIMonsterController::MoveToEnemy()
{
    UBlackboardComponent* BlackboardComponent = BrainComponent->GetBlackboardComponent();

    AActor* HeroCharacterActor = Cast<AActor>(BlackboardComponent->GetValueAsObject("TargetActorToFollow"));

    if (!HeroCharacterActor)
    {
        UE_LOG(LogTemp, Warning, TEXT("MoveToEnemy called but TargetActorToFollow is not set."));
        return EPathFollowingRequestResult::Type::Failed;
    }

    UE_LOG(LogTemp, Log, TEXT("Attempting to move to actor: %s"), *HeroCharacterActor->GetName());

    EPathFollowingRequestResult::Type MoveToActorResult = MoveToActor(HeroCharacterActor);

    if (MoveToActorResult == EPathFollowingRequestResult::Type::RequestSuccessful)
    {
        UE_LOG(LogTemp, Log, TEXT("MoveToActor request successful."));
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("MoveToActor request failed."));
    }

    return MoveToActorResult;
}
