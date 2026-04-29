#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "UE08BaseWeapon.generated.h"

class USkeletalMeshComponent;
class UUE08BarrelComponent;

UCLASS()
class CPP_TEST_API AUE08BaseWeapon : public AActor
{
	GENERATED_BODY()

public:
	AUE08BaseWeapon();

	UFUNCTION(BlueprintCallable, Category = "Weapon")
	void Fire();

	UFUNCTION(BlueprintCallable, Category = "Weapon")
	UUE08BarrelComponent* GetBarrelComponent() const;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<USkeletalMeshComponent> WeaponMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UUE08BarrelComponent> BarrelComponent;
};