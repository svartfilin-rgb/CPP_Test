// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "UE08SpiralStairs.generated.h"


UCLASS()
class CPP_TEST_API AUE08SpiralStairs : public AActor
{
	GENERATED_BODY()


public:	
	// Sets default values for this actor's properties
	AUE08SpiralStairs();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stair Settings")
	UStaticMesh* StepMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stair Settings")
	float StepHeight = 20.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stair Settings")
	int32 Radius = 200;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stair Settings")
	int32 StepsPerTurn = 12;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stair Settings")
	int32 NumberOfTurns = 3;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stair | Geometry")
	float StepThickness = 0.2f;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* InnerCylinder;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stair | Inner Cylinder")
	UStaticMesh* InnerCylinderMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stair | Inner Cylinder")
	float InnerCylinderRadius = 50.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stair | Inner Cylinder")
	float InnerCylinderHeightMultiplier = 1.0f;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void OnConstruction(const FTransform& Transform) override;


	void BuildStair();
	void BuildInnerCylinder();

	UPROPERTY(VisibleAnywhere)
	USceneComponent* Root;
};
