// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UE08BaseCharacter.h"
#include "InputActionValue.h"
#include "InputAction.h"
#include "InputMappingContext.h"

#include "PlayerCharacter.generated.h"




DECLARE_LOG_CATEGORY_EXTERN(LogPlayerCharacter, Log, All);

/**
 * 
 */
UCLASS()
class CPP_TEST_API APlayerCharacter : public AUE08BaseCharacter
{
	GENERATED_BODY()
	
	// METHODS

public:

	APlayerCharacter();



	UFUNCTION(BlueprintCallable, Category = "UE08|Input")
	virtual void DoJumpStart();

	UFUNCTION(BlueprintCallable, Category = "UE08|Input")
	virtual void DoJumpEnd();

	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }

	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }



protected:

	virtual void BeginPlay() override;

	virtual void OnDeath() override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void Move(const FInputActionValue& Value);

	void Look(const FInputActionValue& Value);

private:

	// PROPERTIES

public:


protected:




private:

	//Camera boom positioning the camera behind the character
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UE08|Components", meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;

	//Follow camera
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UE08|Components", meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FollowCamera;

	// Jump Input Action
	UPROPERTY(EditAnywhere, Category = "UE08|Input")
	UInputAction* JumpAction;

	//Move Input Action
	UPROPERTY(EditAnywhere, Category = "UE08|Input")
	UInputAction* MoveAction;


	// Look Input Action
	UPROPERTY(EditAnywhere, Category = "UE08|Input")
	UInputAction* LookAction;

	//Mouse Look Input Action
	UPROPERTY(EditAnywhere, Category = "UE08|Input")
	UInputAction* MouseLookAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	UInputMappingContext* DefaultMappingContext;

};
