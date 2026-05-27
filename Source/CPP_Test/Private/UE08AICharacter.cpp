// Fill out your copyright notice in the Description page of Project Settings.



#include "UE08AICharacter.h"

AUE08AICharacter::AUE08AICharacter()
{
	PrimaryActorTick.bCanEverTick = false;
}

void AUE08AICharacter::BeginPlay()
{
	Super::BeginPlay();
}

AActor* AUE08AICharacter::GetNextPatrolPoint()
{
	if (PatrolPoints.Num() == 0)
	{
		return nullptr;
	}

	AActor* PatrolPoint = PatrolPoints[CurrentPatrolIndex];

	CurrentPatrolIndex = (CurrentPatrolIndex + 1) % PatrolPoints.Num();

	return PatrolPoint;
}