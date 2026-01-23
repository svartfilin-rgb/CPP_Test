#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "NiagaraComponent.h"
#include "NiagaraSystem.h"
#include "MyFirstActor.generated.h"

/*
UENUM(BlueprintType)
enum class EDamageType : uint8
{

Physical UMETA(DisplayName = "Физический", ToolTip = "Обычный Урон"), // - 0
Fire, // - 1
Ice, // - 2
Explosion // - 3

};*/

UCLASS()
class CPP_TEST_API AMyFirstActor : public AActor
{
	GENERATED_BODY()

public:
	AMyFirstActor();

	 
	//Components
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UStaticMeshComponent* Mesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UNiagaraComponent* NiagaraComponent;

	//Variables
	  

	//1️ Health — видно в BP, но нельзя менять
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Stats")
	float Health;

	//2️ Stamina — можно менять в Blueprint
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	float Stamina;

	//3 Strong — можно менять в Blueprint
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	float Strong;

	//4 Armor — только Class Defaults
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Equipment")
	float Armor;

	//5 Weapon — только Instance (на уровне)
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Equipment")
	bool Weapon;



	//Events / Functions
	  

	// 1️ BlueprintImplementableEvent - нельзя редактировать в С++
	UFUNCTION(BlueprintImplementableEvent, Category = "Niagara")
	void OnComponentAdded(const FString& ComponentName);

	// 2️ BlueprintNativeEvent - можно сделать базу в С++, но также можно определить в BP
	UFUNCTION(BlueprintNativeEvent, Category = "Niagara")
	void SetNiagaraEffect(UNiagaraSystem* NiagaraSystem);
	virtual void SetNiagaraEffect_Implementation(UNiagaraSystem* NiagaraSystem);

	// 3️ BlueprintCallable - нельзя редактировать в BP, но можно вызвать (критичная логика)
	UFUNCTION(BlueprintCallable, Category = "Niagara")
	UNiagaraComponent* GetNiagaraComponent() const;


	UFUNCTION(BlueprintPure)
	FVector GetMaxGrabLocation() const;

	UFUNCTION(BlueprintImplementableEvent) 
	void BP_NotifyActor(AActor* Actor);


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	

};