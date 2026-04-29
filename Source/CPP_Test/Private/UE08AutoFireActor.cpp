#include "UE08AutoFireActor.h"
#include "UE08BarrelComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/World.h"
#include "TimerManager.h"

AUE08AutoFireActor::AUE08AutoFireActor()
{
	PrimaryActorTick.bCanEverTick = false;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BaseMesh"));
	RootComponent = BaseMesh;

	BarrelComponent = CreateDefaultSubobject<UUE08BarrelComponent>(TEXT("UE08BarrelComponent"));
	BarrelComponent->SetupAttachment(BaseMesh);
}

void AUE08AutoFireActor::BeginPlay()
{
	Super::BeginPlay();

	if (bAutoFire && FireRate > 0.0f)
	{
		GetWorldTimerManager().SetTimer(
			FireTimerHandle,
			this,
			&AUE08AutoFireActor::HandleFireTimer,
			FireRate,
			true
		);
	}
}

void AUE08AutoFireActor::HandleFireTimer()
{
	if (BarrelComponent)
	{
		BarrelComponent->Fire();
	}
}
