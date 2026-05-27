#include "BTTask_GetNextPatrolPoint.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "UE08AICharacter.h"

UBTTask_GetNextPatrolPoint::UBTTask_GetNextPatrolPoint()
{
	NodeName = TEXT("Get Next Patrol Point");
}

EBTNodeResult::Type UBTTask_GetNextPatrolPoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* AIController = OwnerComp.GetAIOwner();
	if (!AIController)
	{
		return EBTNodeResult::Failed;
	}

	AUE08AICharacter* AICharacter = Cast<AUE08AICharacter>(AIController->GetPawn());
	if (!AICharacter)
	{
		return EBTNodeResult::Failed;
	}

	AActor* NextPatrolPoint = AICharacter->GetNextPatrolPoint();
	if (!NextPatrolPoint)
	{
		return EBTNodeResult::Failed;
	}

	UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();
	if (!BlackboardComp)
	{
		return EBTNodeResult::Failed;
	}

	BlackboardComp->SetValueAsVector(
		DestinationPointKey.SelectedKeyName,
		NextPatrolPoint->GetActorLocation()
	);

	return EBTNodeResult::Succeeded;
}