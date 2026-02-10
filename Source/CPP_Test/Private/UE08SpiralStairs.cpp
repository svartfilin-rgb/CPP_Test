// Fill out your copyright notice in the Description page of Project Settings.


#include "UE08SpiralStairs.h"
#include "Components/SceneComponent.h"
#include "Components/StaticMeshComponent.h"


// Sets default values
AUE08SpiralStairs::AUE08SpiralStairs()
{
 	// 
	PrimaryActorTick.bCanEverTick = false;

    Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);

	InnerCylinder = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("InnerCylinder"));
	InnerCylinder->SetupAttachment(Root);

}



// Called when the game starts or when spawned
void AUE08SpiralStairs::BeginPlay()
{
	Super::BeginPlay();


}



void AUE08SpiralStairs::BuildStair()

{
	int32 TotalSteps = NumberOfTurns * StepsPerTurn; //36
	float AngleStep = 360.0f / StepsPerTurn;

	for (int32 i = 0; i < TotalSteps; i++)
	{
		FString Name = FString::Printf(TEXT("Step_%d"), i);
		UStaticMeshComponent* Step = NewObject<UStaticMeshComponent>(this, *Name);

		Step->SetStaticMesh(StepMesh);
		Step->AttachToComponent(this->GetRootComponent(),FAttachmentTransformRules::KeepRelativeTransform);

		float Angle = FMath::DegreesToRadians(i * AngleStep);
		float X = FMath::Cos(Angle) * Radius;
		float Y = FMath::Sin(Angle) * Radius;
		float Z = i * StepHeight;

		FVector StepLocation = { X, Y, Z };

		Step->SetRelativeLocation(StepLocation);

		FRotator StepRotation = { 0, i * AngleStep, 0 };
		Step->SetRelativeRotation(StepRotation);

		Step->SetRelativeScale3D(FVector(1.f, 1.f, StepThickness));

		Step->RegisterComponent();
	}
	
}

void AUE08SpiralStairs::BuildInnerCylinder()


	{
		if (!InnerCylinder || !InnerCylinderMesh)
			return;

		InnerCylinder->SetStaticMesh(InnerCylinderMesh);

		const float TotalHeight = StepsPerTurn * NumberOfTurns * StepHeight;
		const float HalfHeight = TotalHeight * 0.5f;

		// Cylinder: высота = 100, радиус = 50
		const float MeshRadius = 50.f;
		const float MeshHalfHeight = 50.f;

		const float RadiusScale = InnerCylinderRadius / MeshRadius;
		const float HeightScale = (TotalHeight * InnerCylinderHeightMultiplier) / (MeshHalfHeight * 2.f);

		InnerCylinder->SetRelativeScale3D(FVector(
			RadiusScale,
			RadiusScale,
			HeightScale
		));

		InnerCylinder->SetRelativeLocation(FVector(0.f, 0.f, HalfHeight));
	}


void AUE08SpiralStairs::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	//очистка
	TArray<UActorComponent*> Components;
	GetComponents(UStaticMeshComponent::StaticClass(), Components);

	for (UActorComponent* Comp : Components)
	{
		if (Comp && Comp != InnerCylinder)
		{
			Comp->DestroyComponent();
		}
	}

	if (!StepMesh)
	{
		UE_LOG(LogTemp, Warning, TEXT("StepMesh is not set"));
		return;
	}

	BuildStair();
	BuildInnerCylinder();
}



