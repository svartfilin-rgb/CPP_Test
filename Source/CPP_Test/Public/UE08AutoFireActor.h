#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "UE08AutoFireActor.generated.h"

class UStaticMeshComponent;
class UUE08BarrelComponent;

UCLASS()
class CPP_TEST_API AUE08AutoFireActor : public AActor
{
	GENERATED_BODY()

public:
	AUE08AutoFireActor();

protected:
	virtual void BeginPlay() override;

	void HandleFireTimer();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UStaticMeshComponent> BaseMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UUE08BarrelComponent> BarrelComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Fire")
	bool bAutoFire = true;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Fire")
	float FireRate = 1.0f;

	FTimerHandle FireTimerHandle;
};