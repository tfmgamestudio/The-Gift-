#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Waypoint.h"
#include "Monster.h"

#include "MonsterSpawner.generated.h"

UCLASS()
class THEGIFT_API AMonsterSpawner : public AActor
{
	GENERATED_BODY()

public: 
	AMonsterSpawner();

protected:
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	void StartSpawn();
	
	void SpawnMonsterAtRandomWaypoint();

	UPROPERTY(EditAnywhere, Category = "Spawning")
	TSubclassOf<AMonster> BlueprintMonsterClass;

private:
	UPROPERTY(EditAnywhere)
	TArray<AWaypoint*> Waypoints;

	AMonster* Monster = nullptr;

};
