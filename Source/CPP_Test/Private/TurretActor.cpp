#include "TurretActor.h"
#include "UE08BarrelComponent.h"
#include "Components/StaticMeshComponent.h"
#include "TimerManager.h"
#include "Engine/World.h"

ATurretActor::ATurretActor()
{
	PrimaryActorTick.bCanEverTick = false;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BaseMesh"));
	RootComponent = BaseMesh;

	BarrelComponent = CreateDefaultSubobject<UUE08BarrelComponent>(TEXT("UE08BarrelComponent"));
	BarrelComponent->SetupAttachment(BaseMesh);
}

void ATurretActor::BeginPlay()
{
	Super::BeginPlay();

	if (bAutoFire && FireInterval > 0.0f)
	{
		GetWorldTimerManager().SetTimer(
			FireTimerHandle,
			this,
			&ATurretActor::HandleFireTimer,
			FireInterval,
			true
		);
	}
}

void ATurretActor::HandleFireTimer()
{
	if (BarrelComponent)
	{
		BarrelComponent->Fire();
	}
}