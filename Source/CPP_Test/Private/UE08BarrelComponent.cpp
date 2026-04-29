#include "UE08BarrelComponent.h"
#include "DrawDebugHelpers.h"
#include "Engine/World.h"
#include "GameFramework/Actor.h"
#include "Kismet/GameplayStatics.h"

UUE08BarrelComponent::UUE08BarrelComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UUE08BarrelComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UUE08BarrelComponent::Fire()
{
	if (bUseProjectile)
	{
		FireProjectile();
	}
	else
	{
		FireHitScan();
	}
}

void UUE08BarrelComponent::FireHitScan()
{
	UWorld* World = GetWorld();
	if (!World)
	{
		return;
	}

	const FVector Start = GetComponentLocation();
	const FVector End = Start + GetForwardVector() * TraceDistance;

	FHitResult HitResult;
	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(GetOwner());

	const bool bHit = World->LineTraceSingleByChannel(
		HitResult,
		Start,
		End,
		ECC_Visibility,
		QueryParams
	);

	DrawDebugLine(World, Start, End, FColor::Red, false, 1.0f, 0, 1.5f);

	if (bHit && HitResult.GetActor())
	{
		UE_LOG(LogTemp, Warning, TEXT("Hit actor: %s"), *HitResult.GetActor()->GetName());

		UGameplayStatics::ApplyPointDamage(
			HitResult.GetActor(),
			Damage,
			GetForwardVector(),
			HitResult,
			GetOwner() ? GetOwner()->GetInstigatorController() : nullptr,
			GetOwner(),
			nullptr
		);
	}
}

void UUE08BarrelComponent::FireProjectile()
{
	UWorld* World = GetWorld();
	if (!World || !ProjectileClass)
	{
		return;
	}

	const FVector SpawnLocation = GetComponentLocation();
	const FRotator SpawnRotation = GetComponentRotation();

	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = GetOwner();
	SpawnParams.Instigator = GetOwner() ? GetOwner()->GetInstigator() : nullptr;

	World->SpawnActor<AActor>(
		ProjectileClass,
		SpawnLocation,
		SpawnRotation,
		SpawnParams
	);
}