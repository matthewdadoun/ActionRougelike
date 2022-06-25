// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ActionRoguelike/SGameplayInterface.h"
#include "GameFramework/Actor.h"
#include "SPickupActor.generated.h"

class USphereComponent; 
UCLASS()
class ACTIONROGUELIKE_API ASPickupActor : public AActor, public ISGameplayInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASPickupActor();

protected:
	
	bool bIsActive;

	FTimerHandle ReActivateTimer;

	float RespawnTime; 

	UFUNCTION()
	virtual void Interact_Implementation(APawn* InstigatorPawn) override;
	
	UFUNCTION(BlueprintCallable)
	void ShowPickup();
	UFUNCTION(BlueprintCallable)
	void HidePickup();
	UFUNCTION()
	void SetPowerUpState(bool bNewIsActive);
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
