#include "First_Notify_Actor_.h"

AFirst_Notify_Actor_::AFirst_Notify_Actor_()
{
    PrimaryActorTick.bCanEverTick = false;

    Sphere = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
    Sphere->InitSphereRadius(150.f);
    Sphere->SetCollisionProfileName(TEXT("Trigger"));
    RootComponent = Sphere;

    Sphere->OnComponentBeginOverlap.AddDynamic(
        this,
        &AFirst_Notify_Actor_::OnOverlapBegin
    );
}

void AFirst_Notify_Actor_::BeginPlay()
{
    Super::BeginPlay();
}

void AFirst_Notify_Actor_::OnOverlapBegin(
    UPrimitiveComponent* OverlappedComp,
    AActor* OtherActor,
    UPrimitiveComponent* OtherComp,
    int32 OtherBodyIndex,
    bool bFromSweep,
    const FHitResult& SweepResult)
{
    if (!OtherActor || OtherActor == this)
        return;

    NotifyActor(OtherActor);
}