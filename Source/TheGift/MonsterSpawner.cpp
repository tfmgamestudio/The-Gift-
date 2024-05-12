#include "MonsterSpawner.h"
#include "AIMonsterController.h"

AMonsterSpawner::AMonsterSpawner()
{
    PrimaryActorTick.bCanEverTick = false;
    BlueprintMonsterClass = AMonster::StaticClass();
}

void AMonsterSpawner::BeginPlay()
{
    Super::BeginPlay();

    StartSpawn();
}

void AMonsterSpawner::StartSpawn()
{
    SpawnMonsterAtRandomWaypoint();
}

void AMonsterSpawner::SpawnMonsterAtRandomWaypoint()
{
    if (Waypoints.Num() == 0)
    {
        UE_LOG(LogTemp, Warning, TEXT("No waypoints assigned to the monster spawner."));
        return;
    }

    AWaypoint* RandomWaypoint = Waypoints[FMath::RandRange(0, Waypoints.Num() - 1)];

    FVector SpawnLocation = RandomWaypoint->GetActorLocation();

    // Spawn the blueprint child class of AMonster at the waypoint location
    FActorSpawnParameters SpawnParams;
    SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
    AMonster* SpawnedMonster = GetWorld()->SpawnActor<AMonster>(BlueprintMonsterClass, SpawnLocation, FRotator::ZeroRotator, SpawnParams);

    if (SpawnedMonster)
    {
        UE_LOG(LogTemp, Warning, TEXT("Monster spawned at waypoint: %s"), *RandomWaypoint->GetName());
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Failed to spawn monster."));
    }
}
