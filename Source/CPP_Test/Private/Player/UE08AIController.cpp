#include "Player/UE08AIController.h"
#include "UE08AICharacter.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "TimerManager.h"

AUE08AIController::AUE08AIController()
{
}

void AUE08AIController::BeginPlay()
{
	Super::BeginPlay();
}

void AUE08AIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	AUE08AICharacter* PossessedCharacter = Cast<AUE08AICharacter>(InPawn);
	if (!PossessedCharacter)
	{
		return;
	}

	if (PossessedCharacter->BehaviorTreeAsset)
	{
		RunBehaviorTree(PossessedCharacter->BehaviorTreeAsset);
	}
}

void AUE08AIController::StartSearch()
{
	UBlackboardComponent* BB = GetBlackboardComponent();
	if (!BB)
	{
		return;
	}

	BB->SetValueAsBool(TEXT("IsSearching"), true);

	GetWorld()->GetTimerManager().ClearTimer(SearchTimerHandle);
	GetWorld()->GetTimerManager().SetTimer(
		SearchTimerHandle,
		this,
		&AUE08AIController::StopSearch,
		SearchDuration,
		false
	);
}

void AUE08AIController::StopSearch()
{
	UBlackboardComponent* BB = GetBlackboardComponent();
	if (!BB)
	{
		return;
	}

	BB->SetValueAsBool(TEXT("IsSearching"), false);
}