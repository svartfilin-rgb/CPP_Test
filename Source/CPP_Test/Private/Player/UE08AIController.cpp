// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/UE08AIController.h"
#include "UE08AICharacter.h"
#include "BehaviorTree/BehaviorTree.h"

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