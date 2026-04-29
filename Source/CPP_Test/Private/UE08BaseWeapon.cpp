#include "UE08BaseWeapon.h"
#include "UE08BarrelComponent.h"
#include "Components/SkeletalMeshComponent.h"

AUE08BaseWeapon::AUE08BaseWeapon()
{
	PrimaryActorTick.bCanEverTick = false;

	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WeaponMesh"));
	RootComponent = WeaponMesh;

	BarrelComponent = CreateDefaultSubobject<UUE08BarrelComponent>(TEXT("UE08BarrelComponent"));
	BarrelComponent->SetupAttachment(WeaponMesh);
}

void AUE08BaseWeapon::Fire()
{
	if (BarrelComponent)
	{
		BarrelComponent->Fire();
	}
}

UUE08BarrelComponent* AUE08BaseWeapon::GetBarrelComponent() const
{
	return BarrelComponent;
}
