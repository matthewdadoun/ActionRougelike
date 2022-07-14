// Fill out your copyright notice in the Description page of Project Settings.


#include "SCoin_Pickup.h"

#include "SPlayerState.h"

ASCoin_Pickup::ASCoin_Pickup()
{
	
}

void ASCoin_Pickup::Interact_Implementation(APawn* InstigatorPawn)
{
	if (APawn* Pawn = Cast<APawn>(InstigatorPawn))
	{
		if (ASPlayerState* PS = Cast<ASPlayerState>(Pawn->GetPlayerState()))
		{
			PS->AddCredits(1);
			HideAndCooldownPickup();
		}
	}
}
