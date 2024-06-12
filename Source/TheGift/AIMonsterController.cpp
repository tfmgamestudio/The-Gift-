#include "AIMonsterController.h"
#include "BrainComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Waypoint.h"
#include "Runtime/Engine/Public/EngineUtils.h"
#include <Kismet/KismetSystemLibrary.h>
#include "Components/CapsuleComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Navigation/PathFollowingComponent.h"

AAIMonsterController::AAIMonsterController()
{
    BehaviorTreeComponent = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviorTreeComponent"));

    ShouldLookAroundDuration = 4.5f;
}

void AAIMonsterController::BeginPlay()
{
    Super::BeginPlay();

    if (BehaviorTree)
    {
        RunBehaviorTree(BehaviorTree);
        HasSpawned = true;
        GetBlackboardComponent()->SetValueAsBool("HasSpawned", true);
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
        APawn* pPawn = GetPawn();

        FVector MSStart = pPawn->GetActorLocation();
        FVector MSEnd = MSStart + FVector(0, 0, 15.f);

        TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
        ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECC_Pawn));

        TArray<AActor*> ActorsToIgnore;
        ActorsToIgnore.Add(pPawn);

        TArray<FHitResult> OutHits;

        bool bSphereResult = UKismetSystemLibrary::SphereTraceMultiForObjects(GetWorld(), MSStart, MSEnd, 500.f, ObjectTypes, false, ActorsToIgnore, EDrawDebugTrace::None, OutHits, true);

        UBlackboardComponent* BlackboardComponent = BrainComponent->GetBlackboardComponent();
        
        if (bSphereResult)
        {
            // Player is detected inside the multi-sphere
            if (!bPlayerEnteredMultiSphere)
            {
                UE_LOG(LogTemp, Log, TEXT("Player has entered the multi-sphere."));
                bPlayerEnteredMultiSphere = true;
                bPlayerExitedMultiSphere = false;
            }

            BlackboardComponent->SetValueAsBool("ShouldLookAround", false);

            GetWorldTimerManager().ClearTimer(ShouldLookAroundTimerHandle);
            
            bPlayerFound = false;

            for (const FHitResult& Hit : OutHits)
            {
                ACharacter* pCharacter = Cast<ACharacter>(Hit.GetActor());

                if (pCharacter)
                {
                    FVector LTStart = pPawn->GetActorLocation();
                    FVector LTEnd = pCharacter->GetCapsuleComponent()->GetComponentLocation();

                    TArray<FHitResult> LineTraceHit;
                    TArray<TEnumAsByte<EObjectTypeQuery>> LineObjectTypes;

                    LineObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECC_WorldStatic));

                    bool bLineTraceResult = UKismetSystemLibrary::LineTraceMultiForObjects(GetWorld(), LTStart, LTEnd, LineObjectTypes, false, ActorsToIgnore, EDrawDebugTrace::ForDuration, LineTraceHit, true, FLinearColor::Red, FLinearColor::Green, 2.f);

                    bool bIsObstructed = false;

                    if (bLineTraceResult)
                    {
                        for (const FHitResult& LineHit : LineTraceHit)
                        {
                            if (LineHit.GetActor() != pCharacter)
                            {
                                bIsObstructed = true;
                                break;
                            }
                        }
                    }

                    if (!bIsObstructed)
                    {
                        // Player is visible
                        BlackboardComponent->SetValueAsObject("TargetActorToFollow", pCharacter);

                        float Distance = FVector::Dist(pPawn->GetActorLocation(), pCharacter->GetCapsuleComponent()->GetComponentLocation());
                        
                        UE_LOG(LogTemp, Log, TEXT("Distance to enemy: %f"), Distance);
                        
                        if(Distance < 100.f)
                            BlackboardComponent->SetValueAsBool("Attack", true);
                        else
                            BlackboardComponent->SetValueAsBool("Attack", false);
                        
                        UE_LOG(LogTemp, Log, TEXT("Player detected and visible, moving to enemy."));
                        MoveToEnemy();
                        bPlayerFound = true;
                        break;
                    }
                }
            }
        }
        else
        {
            // Player is not detected inside the multi-sphere
            if (bPlayerEnteredMultiSphere)
            {
                UE_LOG(LogTemp, Log, TEXT("Player has exited the multi-sphere."));
                bPlayerEnteredMultiSphere = false;
                bPlayerExitedMultiSphere = true;
                BlackboardComponent->SetValueAsBool("ShouldLookAround", true);
                BlackboardComponent->SetValueAsObject("TargetActorToFollow", nullptr);

                GetCharacter()->GetCharacterMovement()->MaxWalkSpeed = 0.0f;
                
                GetWorldTimerManager().SetTimer(ShouldLookAroundTimerHandle, this, &AAIMonsterController::ResetShouldLookAround, ShouldLookAroundDuration, false);
            }
        }

        // If the player was previously found but not found in this iteration, reset bPlayerFound
        if (bPlayerFound && OutHits.Num() == 0)
        {
            bPlayerFound = false;
        }
    }
}

void AAIMonsterController::ResetShouldLookAround()
{
    UBlackboardComponent* BlackboardComponent = BrainComponent->GetBlackboardComponent();
    BlackboardComponent->SetValueAsBool("ShouldLookAround", false);

    GetCharacter()->GetCharacterMovement()->MaxWalkSpeed = 200.f;
}

EPathFollowingRequestResult::Type AAIMonsterController::MoveToEnemy()
{
    UBlackboardComponent* BlackboardComponent = BrainComponent->GetBlackboardComponent();
    AActor* HeroCharacterActor = Cast<AActor>(BlackboardComponent->GetValueAsObject("TargetActorToFollow"));
    
    if (!HeroCharacterActor)
    {
        return EPathFollowingRequestResult::Failed;
    }
    
    if (BlackboardComponent->GetValueAsBool("ShouldLookAround"))
    {
        GetCharacter()->GetCharacterMovement()->MaxWalkSpeed = 0.0f;
    }
    else
    {
        GetCharacter()->GetCharacterMovement()->MaxWalkSpeed = 200.f;
    }

    bool bAttack = BlackboardComponent->GetValueAsBool("Attack");

    if (bAttack)
    {
        GetCharacter()->GetCharacterMovement()->MaxWalkSpeed = 0.0f;
    }
    else
    {
        GetCharacter()->GetCharacterMovement()->MaxWalkSpeed = 200.f;
    }

    EPathFollowingRequestResult::Type MoveToActorResult = MoveToActor(HeroCharacterActor);

    return MoveToActorResult;
}
