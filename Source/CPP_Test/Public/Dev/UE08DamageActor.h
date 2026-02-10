// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "UE08DamageActor.generated.h"

UCLASS()
class CPP_TEST_API AUE08DamageActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AUE08DamageActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY (EditAnywhere, BlueprintReadWrite)
	float Radius = 500.0f;

	UPROPERTY (EditAnywhere, BlueprintReadWrite)
	float Segments = 16.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Damage = 20.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UDamageType> DamageType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bDoFullDamage = false;
};
