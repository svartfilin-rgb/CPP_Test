// Fill out your copyright notice in the Description page of Project Settings.


#include "Dev/UE08DamageActor.h"
#include "DrawDebugHelpers.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AUE08DamageActor::AUE08DamageActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AUE08DamageActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AUE08DamageActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	DrawDebugSphere(GetWorld(), GetActorLocation(), Radius, Segments, FColor::Red );
	UGameplayStatics::ApplyRadialDamage(GetWorld(), Damage, GetActorLocation(), Radius, DamageType, {}, this, nullptr, 
		bDoFullDamage, ECollisionChannel::ECC_Visibility );
}

