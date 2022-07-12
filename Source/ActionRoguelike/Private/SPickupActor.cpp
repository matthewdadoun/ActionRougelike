// Fill out your copyright notice in the Description page of Project Settings.


#include "SPickupActor.h"

#include "Net/UnrealNetwork.h"

// Sets default values
ASPickupActor::ASPickupActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	RespawnTime = 10;

	SetReplicates(true);
}

void ASPickupActor::OnRep_IsActive()
{
	SetActorEnableCollision(bIsActive);
	RootComponent->SetVisibility(bIsActive, true);
}

void ASPickupActor::Interact_Implementation(APawn* InstigatorPawn)
{
	ISGameplayInterface::Interact_Implementation(InstigatorPawn);
}

void ASPickupActor::ShowPickup()
{
	SetPickupState(true);
}

void ASPickupActor::HidePickup()
{
	SetPickupState(false);

	GetWorldTimerManager().SetTimer(ReActivateTimer, this, &ThisClass::ShowPickup, 10);
}

void ASPickupActor::SetPickupState(bool bNewIsActive)
{
	bIsActive = bNewIsActive;
	OnRep_IsActive();
}

// Called every frame
void ASPickupActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ASPickupActor::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ThisClass, bIsActive);
}
