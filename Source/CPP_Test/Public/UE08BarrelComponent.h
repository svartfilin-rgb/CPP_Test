#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "UE08BarrelComponent.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class CPP_TEST_API UUE08BarrelComponent : public USceneComponent
{
	GENERATED_BODY()

public:
	UUE08BarrelComponent();

	UFUNCTION(BlueprintCallable, Category = "Weapon")
	void Fire();

protected:
	virtual void BeginPlay() override;

	void FireHitScan();
	void FireProjectile();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Fire")
	bool bUseProjectile = false;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Fire", meta = (EditCondition = "!bUseProjectile"))
	float TraceDistance = 10000.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Fire", meta = (EditCondition = "!bUseProjectile"))
	float Damage = 20.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Fire", meta = (EditCondition = "bUseProjectile"))
	TSubclassOf<AActor> ProjectileClass;
};