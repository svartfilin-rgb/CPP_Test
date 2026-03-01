// Fill out your copyright notice in the Description page of Project Settings.


#include "UE08TriggerPlatform.h"
#include "Components/BoxComponent.h"
#include "Net/UnrealNetwork.h"

// Sets default values
AUE08TriggerPlatform::AUE08TriggerPlatform()
{
	PrimaryActorTick.bCanEverTick = false;
	bReplicates = true;

	PlatformMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PlatformMesh"));
	SetRootComponent(PlatformMesh);

	TriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox"));
	TriggerBox->SetupAttachment(PlatformMesh);

	// Настройка коллизии триггера
	TriggerBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	TriggerBox->SetCollisionResponseToAllChannels(ECR_Ignore);
	TriggerBox->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
}

void AUE08TriggerPlatform::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	FDoRepLifetimeParams RepParams;
	RepParams.RepNotifyCondition = REPNOTIFY_Always;

	DOREPLIFETIME_WITH_PARAMS(AUE08TriggerPlatform, bIsActivated, RepParams);

	//DOREPLIFETIME(AUE08TriggerPlatform, bIsActivated);
}

void AUE08TriggerPlatform::BeginPlay()
{
	Super::BeginPlay();

	TriggerBox->OnComponentBeginOverlap.AddDynamic(this, &AUE08TriggerPlatform::OnTriggerOverlapBegin);
	TriggerBox->OnComponentEndOverlap.AddDynamic(this, &AUE08TriggerPlatform::OnTriggerOverlapEnd);
}

//
// Вызывается на клиентах при изменении bIsActivated
//
void AUE08TriggerPlatform::OnRep_IsActivated(bool bIsActivated_Old)
{
	OnTriggerActivated.Broadcast(bIsActivated);
}

//
// Меняет состояние (вызывается ТОЛЬКО на сервере)
//
void AUE08TriggerPlatform::SetIsActivated(bool bIsActivated_In)
{
	if (!HasAuthority())
		return;

	bIsActivated = bIsActivated_In;

	// На сервере OnRep не вызывается автоматически,
	// поэтому вызываем вручную
	OnRep_IsActivated(!bIsActivated_In);
}

//
//зашёл в триггер
//
void AUE08TriggerPlatform::OnTriggerOverlapBegin(
	UPrimitiveComponent* OverlapComponent,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult& SweepResult)
{
	APawn* OtherPawn = Cast<APawn>(OtherActor);

	if (!IsValid(OtherPawn))
		return;

	if (!HasAuthority())
		return;

	if (OtherPawn->IsLocallyControlled() || GetLocalRole() == ROLE_Authority)
	{

		OverlappedPawns.AddUnique(OtherPawn);

		if (!bIsActivated && OverlappedPawns.Num() > 0)
		{
			bIsActivated = true;
			//SetIsActivated(true);
		}
	}
}

//
//вышел из триггера
//
void AUE08TriggerPlatform::OnTriggerOverlapEnd(
	UPrimitiveComponent* OverlapComponent,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex)
{
	APawn* OtherPawn = Cast<APawn>(OtherActor);

	if (!IsValid(OtherPawn))
		return;

	if (!HasAuthority())
		return;

	OverlappedPawns.RemoveSingleSwap(OtherPawn);

	if (OtherPawn->IsLocallyControlled() || GetLocalRole() == ROLE_Authority)
	{

		if (bIsActivated && OverlappedPawns.Num() == 0)
		{
			bIsActivated = false;
			//SetIsActivated(false);
		}
	}
}

void AUE08TriggerPlatform::OnPlatformTriggerActivated(bool bIsActivated_In)
{
	// М
}

//
