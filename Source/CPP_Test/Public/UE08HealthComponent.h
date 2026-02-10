#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "UE08HealthComponent.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LogUE08HealthComponent, All, All)

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDeathSignature);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(
	FOnHealthChangedSignature,
	float, Health,
	float, HealthDelta
);





UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class CPP_TEST_API UUE08HealthComponent : public UActorComponent
{
	GENERATED_BODY()

	//METHODS

public:
	// Sets default values for this component's properties
	UUE08HealthComponent();


protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UFUNCTION()
	FORCEINLINE float GetHealth() { return Health; };

	UFUNCTION()
	void OnTakeAnyDamage(AActor* DamagedActor, float Damage,
		const UDamageType* DamageType,
		AController* InstigatedBy,
		AActor* DamageCauser);
	//void GetDamage(AActor* DamageActor, float Damage, class AController* instigatedBy,
	//	AActor* DamageCauser, const class UDamageType* DamageType);

	UFUNCTION()
	void SetHealth(float newHealth);

	UFUNCTION()
	bool IsDead() const {
		return FMath::IsNearlyZero(Health);
	};

	//PROPERTIES
public:

	UPROPERTY()
	float MaxHealth = 100.0f;

	UPROPERTY(BlueprintAssignable)
	FOnDeathSignature OnDeath;

	UPROPERTY(BlueprintAssignable)
	FOnHealthChangedSignature OnHealthChanged;

protected:


private:

	UPROPERTY()
	float Health = 0.0f;

};