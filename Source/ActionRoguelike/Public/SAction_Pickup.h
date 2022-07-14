// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SPickupActor.h"
#include "SAction_Pickup.generated.h"

/**
 * 
 */
class USAction;
UCLASS()
class ACTIONROGUELIKE_API ASAction_Pickup : public ASPickupActor
{
	GENERATED_BODY()

public:

	virtual void Interact_Implementation(APawn* InstigatorPawn) override;
	ASAction_Pickup();

protected:

	UPROPERTY(EditDefaultsOnly, Category = "Pickup")
	UStaticMeshComponent* ActionMeshComp;

	UPROPERTY(EditDefaultsOnly, Category = "Pickup")
	TSubclassOf<USAction> ActionToAdd;
};
