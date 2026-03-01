// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "UE08Mover.generated.h"

class UStaticMeshComponent;
class UBoxComponent;
class UCurveFloat;
class UNiagaraSystem;
class UNiagaraComponent;

UCLASS()
class CPP_TEST_API AUE08Mover : public AActor
{
	GENERATED_BODY()

public:
	AUE08Mover();
	virtual void Tick(float DeltaSeconds) override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

protected:
	virtual void BeginPlay() override;

	// ---------- Trigger ----------
	UFUNCTION()
	void OnTriggerBegin(UPrimitiveComponent* OverlapComp, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
		const FHitResult& SweepResult);

	UFUNCTION()
	void OnTriggerEnd(UPrimitiveComponent* OverlapComp, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	// ---------- Replication ----------
	// Состояние движения (вверх/вниз/стоп) и "серверное время старта"
	UFUNCTION()
	void OnRep_MoveState();

	UFUNCTION(Server, Reliable)
	void ServerSetMoving(bool bNewMovingUp);

	UFUNCTION(NetMulticast, Unreliable)
	void MulticastCosmeticPulse(); // только визуалка (можно спамить, поэтому Unreliable)

	// ---------- Helpers ----------
	void SetMoveState_Server(bool bNewMovingUp);
	void ApplyMovement(float Alpha);
	void ClientOnly_ApplyCosmetics(bool bActive);

public:
	// ---------- Components ----------
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Mover")
	USceneComponent* Root;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Mover")
	UStaticMeshComponent* Mesh;

	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Mover")
	//UBoxComponent* Trigger;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mover")
	//UBoxComponent* Trigger = nullptr;

	// ---------- Settings (Blueprint) ----------
	// Кривая таймлайна: X=0..1 (время), Y=0..1 (альфа)
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Mover|Timeline")
	UCurveFloat* MoveCurve = nullptr;

	// Длительность движения в секундах
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Mover|Timeline", meta = (ClampMin = "0.01"))
	float Duration = 1.5f;

	// Смещение (куда едем относительно старта)
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Mover|Movement")
	FVector LocalOffset = FVector(0.f, 0.f, 200.f);

	// Если true — при выходе из триггера возвращаемся обратно
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Mover|Movement")
	bool bReturnOnEndOverlap = true;

	// Включить/выключить движение
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Mover|Movement")
	bool bEnabled = true;

	// ---------- Client-only cosmetics ----------
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Mover|Cosmetics")
	UMaterialInterface* ActiveMaterial = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Mover|Cosmetics")
	UMaterialInterface* InactiveMaterial = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Mover|Cosmetics")
	UNiagaraSystem* ActiveFX = nullptr;

private:
	// ---------- Runtime ----------
	FTransform StartTransform;

	// кто сейчас внутри триггера (сервер решает)
	UPROPERTY()
	TArray<TWeakObjectPtr<APawn>> OverlappedPawns;

	// Реплицируемое состояние:
	// bMovingUp = true -> движемся к Offset, false -> возвращаемся к старту
	UPROPERTY(ReplicatedUsing = OnRep_MoveState)
	bool bMovingUp = false;

	// Серверное время, когда началось текущее движение
	UPROPERTY(ReplicatedUsing = OnRep_MoveState)
	float MoveStartServerTime = 0.f;

	// Niagara component на клиенте (не реплицируем)
	UPROPERTY(Transient)
	UNiagaraComponent* SpawnedFX = nullptr;

	// --------- Delay / Lock ----------
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Mover|Timeline", meta = (ClampMin = "0.0", AllowPrivateAccess = "true"))
	float ActivationDelay = 1.0f;

	// true = сейчас ждём задержку перед стартом
	UPROPERTY(Transient)
	bool bPendingActivation = false;

	// true = сейчас идёт движение (мы ещё не дошли до конца)
	UPROPERTY(Transient)
	bool bInMotion = false;

	FTimerHandle TimerHandle_ActivateDelayed;

	// серверный старт с задержкой
	void StartMoveDelayed_Server(bool bNewMovingUp);

	// вызывается таймером
	void DelayedStart_Execute(bool bNewMovingUp);

	// проверка "доехали ли до конца"
	bool HasReachedEnd(float T01) const;


};