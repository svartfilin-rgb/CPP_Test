#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TurretActor.generated.h"

class UStaticMeshComponent;
class UUE08BarrelComponent;

UCLASS()
class CPP_TEST_API ATurretActor : public AActor
{
	GENERATED_BODY()

public:
	ATurretActor();

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	void HandleFireTimer();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UStaticMeshComponent> BaseMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UUE08BarrelComponent> BarrelComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Fire")
	bool bAutoFire = true;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Fire")
	float FireInterval = 5.0f;

	FTimerHandle FireTimerHandle;
};