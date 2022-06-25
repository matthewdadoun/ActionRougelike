// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SPickupActor.h"
#include "SHealthPotion_Pickup.generated.h"

/**
 * 
 */
UCLASS()
class ACTIONROGUELIKE_API ASHealthPotion_Pickup : public ASPickupActor
{
	GENERATED_BODY()

public:
	UFUNCTION()
	void RefillHealth(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	virtual void BeginPlay() override;

	ASHealthPotion_Pickup();
protected:
	virtual void Interact_Implementation(APawn* InstigatorPawn) override;

	
	UPROPERTY(EditDefaultsOnly, Category = "Pickup")
	UStaticMeshComponent* PotionBottleMeshComp; 
};
