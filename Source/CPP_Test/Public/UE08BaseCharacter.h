#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "UE08BaseCharacter.generated.h"

UCLASS()
class CPP_TEST_API AUE08BaseCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Methods **/


public:
	// Sets default values for this character's properties
	AUE08BaseCharacter();

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	virtual void OnDeath();

private:

	/** Properties **/

public:

protected:

private:


};