// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "UE08AIController.generated.h"


UCLASS()
class CPP_TEST_API AUE08AIController : public AAIController
{
	GENERATED_BODY()
	
public:
	AUE08AIController();

protected:

	virtual void BeginPlay() override;

	virtual void OnPossess(APawn* InPawn) override;


};
