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
	
	UFUNCTION()
	void AddAction(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	ASAction_Pickup();

protected:

	UPROPERTY(EditDefaultsOnly, Category = "Pickup")
	UStaticMeshComponent* ActionMeshComp;

	UPROPERTY(EditDefaultsOnly, Category = "Pickup")
	TSubclassOf<USAction> ActionToAdd;
};
