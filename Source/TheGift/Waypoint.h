#pragma once

#include "CoreMinimal.h"
#include "Engine/TargetPoint.h"
#include "Waypoint.generated.h"


UCLASS()
class THEGIFT_API AWaypoint : public ATargetPoint
{
	GENERATED_BODY()
	
public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 m_iPosition;
};
