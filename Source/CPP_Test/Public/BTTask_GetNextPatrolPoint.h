#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BehaviorTree/BehaviorTreeTypes.h"
#include "BTTask_GetNextPatrolPoint.generated.h"

UCLASS()
class CPP_TEST_API UBTTask_GetNextPatrolPoint : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UBTTask_GetNextPatrolPoint();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Blackboard")
	FBlackboardKeySelector DestinationPointKey;

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};