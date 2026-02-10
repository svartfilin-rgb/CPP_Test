// Fill out your copyright notice in the Description page of Project Settings.


#include "UE08PlayerController.h"
#include "EnhancedInputSubsystems.h"

//
void AUE08PlayerController::BeginPlay()
{
	Super::BeginPlay();
}

//
void AUE08PlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());

	if (IsLocalPlayerController())
	{
		if (Subsystem)
		{
			for (UInputMappingContext* CurrentContext : DefaultMappingContexts)
			{
				Subsystem->AddMappingContext(CurrentContext, 0);
			}

			

		}
	}
}
