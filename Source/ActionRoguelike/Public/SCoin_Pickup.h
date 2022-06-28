// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SPickupActor.h"
#include "SCoin_Pickup.generated.h"

/**
 * 
 */

UCLASS()
class ACTIONROGUELIKE_API ASCoin_Pickup : public ASPickupActor
{
	GENERATED_BODY()
public:
	UFUNCTION()
	void AddCredit(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	ASCoin_Pickup();

protected:

	UPROPERTY(EditDefaultsOnly, Category = "Pickup")
	UStaticMeshComponent* CoinMeshComp; 
};
