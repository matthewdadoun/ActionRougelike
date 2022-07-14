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
	
	ASCoin_Pickup();

protected:

	UPROPERTY(EditDefaultsOnly, Category = "Pickup")
	UStaticMeshComponent* CoinMeshComp;

	virtual void Interact_Implementation(APawn* InstigatorPawn) override;
};
