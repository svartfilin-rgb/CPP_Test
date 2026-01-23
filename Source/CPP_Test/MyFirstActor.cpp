#include "MyFirstActor.h"

AMyFirstActor::AMyFirstActor()
{
	PrimaryActorTick.bCanEverTick = false;

	// Create Mesh component
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	RootComponent = Mesh;

	// Niagara
	NiagaraComponent = CreateDefaultSubobject<UNiagaraComponent>(TEXT("NiagaraComponent_test"));
	NiagaraComponent->SetupAttachment(RootComponent);


	Health = 100.0f;
	Stamina = 50.0f;
	Armor = 25.0f;
	Strong = 25.0f;
	Weapon = false;
	
}

	// Вызываем Blueprint-события ТОЛЬКО после BeginPlay
	void AMyFirstActor::BeginPlay()
{
	Super::BeginPlay();

	if (NiagaraComponent)
	{
		OnComponentAdded(NiagaraComponent->GetName());
	}
}


// 2️⃣ BlueprintNativeEvent (C++ fallback)
void AMyFirstActor::SetNiagaraEffect_Implementation(UNiagaraSystem* NiagaraSystem)
{
	if (NiagaraComponent && NiagaraSystem)
	{
		NiagaraComponent->SetAsset(NiagaraSystem);

		UE_LOG(LogTemp, Log,
			TEXT("Niagara asset set: %s"),
			*NiagaraSystem->GetName());
	}
	else
	{
		UE_LOG(LogTemp, Warning,
			TEXT("SetNiagaraEffect failed: NiagaraComponent or NiagaraSystem is NULL"));
	}
}

FVector AMyFirstActor::GetMaxGrabLocation() const
{
	return GetActorLocation() + FVector(100.f, 0.f, 0.f);
}

// 3️⃣ BlueprintCallable
UNiagaraComponent* AMyFirstActor::GetNiagaraComponent() const
{
	return NiagaraComponent;
}