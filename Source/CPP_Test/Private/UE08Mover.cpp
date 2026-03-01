// Fill out your copyright notice in the Description page of Project Settings.

#include "UE08Mover.h"

#include "TimerManager.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "Net/UnrealNetwork.h"
#include "Curves/CurveFloat.h"
#include "GameFramework/GameStateBase.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"

AUE08Mover::AUE08Mover()
{
	PrimaryActorTick.bCanEverTick = true;
	bReplicates = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(Root);
	Mesh->SetIsReplicated(false); // двигаем вручную по таймлайну на всех

	//Trigger = CreateDefaultSubobject<UBoxComponent>(TEXT("Trigger"));
	//Trigger->SetupAttachment(Root);
	//Trigger->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	//Trigger->SetCollisionResponseToAllChannels(ECR_Ignore);
	//Trigger->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
}

void AUE08Mover::BeginPlay()
{
	Super::BeginPlay();

	StartTransform = Mesh->GetRelativeTransform();

	UBoxComponent* Trigger = FindComponentByClass<UBoxComponent>();

	if (!Trigger)
	{
		UE_LOG(LogTemp, Error, TEXT("No BoxComponent found on Mover!"));
		return;
	}

	Trigger->OnComponentBeginOverlap.AddDynamic(this, &AUE08Mover::OnTriggerBegin);
	Trigger->OnComponentEndOverlap.AddDynamic(this, &AUE08Mover::OnTriggerEnd);
	

	// Инициализация косметики на клиентах
	if (!HasAuthority())
	{
		ClientOnly_ApplyCosmetics(false);
	}
}

void AUE08Mover::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (!bEnabled || !MoveCurve)
		return;

	// Если ещё не начинали движение (MoveStartServerTime = 0), но мы "в ожидании" — ничего не делаем
	if (MoveStartServerTime <= 0.f)
		return;

	const AGameStateBase* GS = GetWorld() ? GetWorld()->GetGameState() : nullptr;
	const float NowServer = GS ? GS->GetServerWorldTimeSeconds() : GetWorld()->GetTimeSeconds();

	const float Elapsed = FMath::Max(0.f, NowServer - MoveStartServerTime);
	const float T = (Duration > 0.f) ? FMath::Clamp(Elapsed / Duration, 0.f, 1.f) : 1.f;

	const float CurveAlpha = MoveCurve->GetFloatValue(T);
	const float FinalAlpha = bMovingUp ? CurveAlpha : (1.f - CurveAlpha);

	ApplyMovement(FinalAlpha);

	if (HasAuthority() && bInMotion)
	{
		// если дошли до конца (T==1) — снимаем lock
		if (HasReachedEnd(T))
		{
			bInMotion = false;
			// после завершения движения можно снова активировать
		}
	}
}

bool AUE08Mover::HasReachedEnd(float T01) const
{
	// Дошли до конца таймлайна
	return (T01 >= 1.0f - KINDA_SMALL_NUMBER);
}


void AUE08Mover::ApplyMovement(float Alpha)
{
	// Локально между StartTransform и StartTransform + Offset
	const FVector StartLoc = StartTransform.GetLocation();
	const FVector TargetLoc = StartLoc + LocalOffset;
	const FVector NewLoc = FMath::Lerp(StartLoc, TargetLoc, Alpha);

	Mesh->SetRelativeLocation(NewLoc);
}

void AUE08Mover::OnTriggerBegin(UPrimitiveComponent* OverlapComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
	const FHitResult& SweepResult)
{
	if (!bEnabled)
		return;

	APawn* Pawn = Cast<APawn>(OtherActor);
	if (!IsValid(Pawn))
		return;

	if (!HasAuthority())
		return;

	OverlappedPawns.AddUnique(Pawn);

	// Уже движемся или ждём старт — ничего не делаем
	if (bInMotion || bPendingActivation)
		return;

	// Если уже активированы "вверх" — тоже ничего
	if (bMovingUp)
		return;

	// Запуск вверх с задержкой
	StartMoveDelayed_Server(true);
}


void AUE08Mover::OnTriggerEnd(UPrimitiveComponent* OverlapComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (!bEnabled || !bReturnOnEndOverlap)
		return;

	APawn* Pawn = Cast<APawn>(OtherActor);
	if (!IsValid(Pawn))
		return;

	if (!HasAuthority())
		return;

	OverlappedPawns.RemoveSingleSwap(Pawn);

	// Если кто-то ещё остался — не выключаем
	if (OverlappedPawns.Num() > 0)
		return;

	// Уже движемся или ждём старт — не вмешиваемся
	if (bInMotion || bPendingActivation)
		return;

	// Если уже "вниз" — нечего делать
	if (!bMovingUp)
		return;

	// Запуск вниз с задержкой
	StartMoveDelayed_Server(false);
}

void AUE08Mover::StartMoveDelayed_Server(bool bNewMovingUp)
{
	if (!HasAuthority())
		return;

	// Лочим повторные активации до старта
	bPendingActivation = true;

	// Сбросим время старта, чтобы Tick не двигал пока ждём
	MoveStartServerTime = 0.f;

	// Можно дать косметический пульс сразу (опционально)
	MulticastCosmeticPulse();

	// Запускаем таймер
	FTimerDelegate Del;
	Del.BindUObject(this, &AUE08Mover::DelayedStart_Execute, bNewMovingUp);

	GetWorldTimerManager().SetTimer(
		TimerHandle_ActivateDelayed,
		Del,
		ActivationDelay,
		false
	);
}

void AUE08Mover::DelayedStart_Execute(bool bNewMovingUp)
{
	if (!HasAuthority())
		return;

	bPendingActivation = false;

	// Если это было включение вверх, но все вышли пока мы ждали — не стартуем
	if (bNewMovingUp)
	{
		if (OverlappedPawns.Num() == 0)
		{
			// никого нет — отменяем
			return;
		}
	}

	// Если это возврат вниз, но кто-то снова зашёл за время ожидания — можно отменить возврат
	if (!bNewMovingUp)
	{
		if (OverlappedPawns.Num() > 0)
		{
			// снова вошли — не возвращаем
			return;
		}
	}

	// Теперь реально запускаем движение и лочим до окончания
	bInMotion = true;

	// Используем твою серверную установку состояния:
	SetMoveState_Server(bNewMovingUp);
}

void AUE08Mover::SetMoveState_Server(bool bNewMovingUp)
{
	if (!HasAuthority())
		return;

	bMovingUp = bNewMovingUp;

	const AGameStateBase* GS = GetWorld() ? GetWorld()->GetGameState() : nullptr;
	MoveStartServerTime = GS ? GS->GetServerWorldTimeSeconds() : GetWorld()->GetTimeSeconds();

	// listen-server тоже получит визуал
	OnRep_MoveState();
}

void AUE08Mover::ServerSetMoving_Implementation(bool bNewMovingUp)
{
	SetMoveState_Server(bNewMovingUp);
}

void AUE08Mover::OnRep_MoveState()
{
	// Визуальные изменения должны быть ТОЛЬКО на клиентах (и на listen-сервере как на клиенте тоже ок)
	// Чтобы не трогать Dedicated Server:
	if (GetNetMode() == NM_DedicatedServer)
		return;

	ClientOnly_ApplyCosmetics(bMovingUp);
}

void AUE08Mover::ClientOnly_ApplyCosmetics(bool bActive)
{
	// Материал
	if (Mesh)
	{
		if (bActive && ActiveMaterial)      Mesh->SetMaterial(0, ActiveMaterial);
		else if (!bActive && InactiveMaterial) Mesh->SetMaterial(0, InactiveMaterial);
	}

	// Niagara: включаем/выключаем
	if (bActive)
	{
		if (!SpawnedFX && ActiveFX)
		{
			SpawnedFX = UNiagaraFunctionLibrary::SpawnSystemAttached(
				ActiveFX,
				Mesh,
				NAME_None,
				FVector::ZeroVector,
				FRotator::ZeroRotator,
				EAttachLocation::KeepRelativeOffset,
				false
			);
		}
	}
	else
	{
		if (SpawnedFX)
		{
			SpawnedFX->Deactivate();
			SpawnedFX = nullptr;
		}
	}
}

void AUE08Mover::MulticastCosmeticPulse_Implementation()
{
	// Это чисто “пульс” (звук/эффект) — делаем только на клиентах
	if (GetNetMode() == NM_DedicatedServer)
		return;

	// Например: краткий эффект при смене состояния
	// Если нужно — можно тут SpawnSystemAtLocation, PlaySoundAtLocation и т.п.
}

void AUE08Mover::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AUE08Mover, bMovingUp);
	DOREPLIFETIME(AUE08Mover, MoveStartServerTime);
}