// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/UE08Character.h"

// Sets default values
AUE08Character::AUE08Character()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AUE08Character::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AUE08Character::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AUE08Character::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

