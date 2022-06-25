// Fill out your copyright notice in the Description page of Project Settings.


#include "SPickupActor.h"

#include "Components/SphereComponent.h"

// Sets default values
ASPickupActor::ASPickupActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

void ASPickupActor::Interact_Implementation(APawn* InstigatorPawn)
{
	ISGameplayInterface::Interact_Implementation(InstigatorPawn);
}

void ASPickupActor::ShowPickup()
{
	SetPowerUpState(true);
}

void ASPickupActor::HidePickup()
{
	SetPowerUpState(false);

	GetWorldTimerManager().SetTimer(ReActivateTimer, this, &ThisClass::ShowPickup, RespawnTime);
}

void ASPickupActor::SetPowerUpState(bool bNewIsActive)
{
	SetActorEnableCollision(bNewIsActive);
	RootComponent->SetVisibility(bNewIsActive, true);
}

// Called every frame
void ASPickupActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

