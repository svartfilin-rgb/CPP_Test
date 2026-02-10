// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "UE08PlayerController.generated.h"

/**
 * 
 */
UCLASS()
class CPP_TEST_API AUE08PlayerController : public APlayerController
{
	GENERATED_BODY()
	

	//METHODS

protected:

	virtual void BeginPlay() override;

	virtual void SetupInputComponent() override;

	//PROPERTIES

protected:

	//Input Mapping Contexts
	UPROPERTY(EditAnywhere, Category = "UE08|Input|Input Mappings")
	TArray<class UInputMappingContext*> DefaultMappingContexts;

};
