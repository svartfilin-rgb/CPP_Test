// Fill out your copyright notice in the Description page of Project Settings.


#include "UE08HealthComponent.h"
#include "GameFramework/Actor.h"
#include "Kismet/GameplayStatics.h"

DEFINE_LOG_CATEGORY(LogUE08HealthComponent);

// Sets default values for this component's properties
UUE08HealthComponent::UUE08HealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void UUE08HealthComponent::BeginPlay()
{
	Super::BeginPlay();

	Health = MaxHealth;

	if (GetOwner())
	{
		GetOwner()->OnTakeAnyDamage.AddDynamic(this, &UUE08HealthComponent::OnTakeAnyDamage);
	}

	UE_LOG(LogUE08HealthComponent, Warning, TEXT("Health Component Was created"));
	// ...

}
//
//void UUE08HealthComponent::GetDamage(AActor* DamageActor, float Damage, AController* instigatedBy, 
//	AActor* DamageCauser, const UDamageType* DamageType)
void UUE08HealthComponent::OnTakeAnyDamage(AActor* DamagedActor, float Damage,
	const UDamageType* DamageType,
	AController* InstigatedBy,
	AActor* DamageCauser)

{
	if (Damage <= 0.0f || IsDead())
	{
		return;
	}

	float newHealth = Health - Damage;

	UE_LOG(LogUE08HealthComponent, Warning, TEXT("Character get %f damage/ Current health is^ %f"), Damage, newHealth);
	SetHealth(newHealth);

	if (IsDead())
	{
		OnDeath.Broadcast();
		UE_LOG(LogUE08HealthComponent, Error, TEXT("Player is dead!"));
	}
}
//
void UUE08HealthComponent::SetHealth(float newHealth)
{
	float UpdatedHealth = FMath::Clamp(newHealth, 0.0f, MaxHealth);
	float HealthDelta = UpdatedHealth - Health;

	Health = UpdatedHealth;

	OnHealthChanged.Broadcast(Health, HealthDelta);
}



