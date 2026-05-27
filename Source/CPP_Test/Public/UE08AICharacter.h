// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UE08BaseCharacter.h"
#include "UE08AICharacter.generated.h"

class UBehaviorTree;

UCLASS()
class CPP_TEST_API AUE08AICharacter : public AUE08BaseCharacter
{
	GENERATED_BODY()

public:

	AUE08AICharacter();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	TObjectPtr<UBehaviorTree> BehaviorTreeAsset;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "AI")
	TArray<TObjectPtr<AActor>> PatrolPoints;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI")
	int32 CurrentPatrolIndex = 0;

	AActor* GetNextPatrolPoint();

protected:

	virtual void BeginPlay() override;

};
