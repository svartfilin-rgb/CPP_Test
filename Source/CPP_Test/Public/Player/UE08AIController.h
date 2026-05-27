#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "UE08AIController.generated.h"

class UBehaviorTreeComponent;
class UBlackboardComponent;

UCLASS()
class CPP_TEST_API AUE08AIController : public AAIController
{
	GENERATED_BODY()

public:
	AUE08AIController();

	virtual void OnPossess(APawn* InPawn) override;
	virtual void BeginPlay() override;

	void StartSearch();
	void StopSearch();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	float SearchDuration = 5.0f;

	FTimerHandle SearchTimerHandle;
};
