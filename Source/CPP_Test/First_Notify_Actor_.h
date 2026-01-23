#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SphereComponent.h"
#include "First_Notify_Actor_.generated.h"

UCLASS()
class CPP_TEST_API AFirst_Notify_Actor_ : public AActor
{
    GENERATED_BODY()

public:
    AFirst_Notify_Actor_();

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    USphereComponent* Sphere;

    UFUNCTION(BlueprintImplementableEvent)
    void NotifyActor(AActor* OtherActor);

protected:
    virtual void BeginPlay() override;

    UFUNCTION()
    void OnOverlapBegin(
        UPrimitiveComponent* OverlappedComp,
        AActor* OtherActor,
        UPrimitiveComponent* OtherComp,
        int32 OtherBodyIndex,
        bool bFromSweep,
        const FHitResult& SweepResult
    );
};