// Fill out your copyright notice in the Description page of Project Settings.


#include "SCoin_Pickup.h"

#include "SPlayerState.h"

void ASCoin_Pickup::AddCredit(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (APawn* Pawn = Cast<APawn>(OtherActor))
	{
		if (ASPlayerState* PS = Cast<ASPlayerState>(Pawn->GetPlayerState()))
		{
			PS->AddCredits(1);
			HidePickup();
		}
	}
}

ASCoin_Pickup::ASCoin_Pickup()
{
	CoinMeshComp = CreateDefaultSubobject<UStaticMeshComponent>("CoinMeshComp");
	RootComponent = CoinMeshComp;

	CoinMeshComp->OnComponentBeginOverlap.AddUniqueDynamic(this, &ThisClass::AddCredit);
}
