// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "UE08TriggerPlatform.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnTriggerBoxActivatedSignature, bool, bIsActivated);

UCLASS()
class CPP_TEST_API AUE08TriggerPlatform : public AActor
{
	GENERATED_BODY()
	
	//Methods

public:	
	// 
	AUE08TriggerPlatform();

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

protected:
	// 
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnRep_IsActivated(bool bIsActivated_Old);

	UFUNCTION()
	void SetIsActivated(bool bIsActivated_In);

private:

	UFUNCTION()
	void OnTriggerOverlapBegin(UPrimitiveComponent* OverlapComponent,
		AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void OnTriggerOverlapEnd(UPrimitiveComponent* OverlapComponent,
		AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyInde);

	UFUNCTION()
	void OnPlatformTriggerActivated(bool bIsActivated_In);

	//Properties
public:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UStaticMeshComponent* PlatformMesh;
    
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	class UBoxComponent* TriggerBox;

	UPROPERTY(BlueprintAssignable)
	FOnTriggerBoxActivatedSignature OnTriggerActivated;

protected:

	
	UPROPERTY(ReplicatedUsing = OnRep_IsActivated)
	bool bIsActivated = false;

	

private:
	TArray<APawn*>OverlappedPawns;

};
