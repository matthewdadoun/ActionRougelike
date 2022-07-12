// Fill out your copyright notice in the Description page of Project Settings.


#include "SPlayerState.h"

#include "Net/UnrealNetwork.h"

void ASPlayerState::AddCredits(float Delta)
{
	Credits += Delta;

	OnCreditsChanged.Broadcast(this, Credits, Delta);
}

bool ASPlayerState::RemoveCredits(float Delta)
{
	if (!ensure(Delta > 0))
	{
		return false;
	}

	if (Credits > 0)
	{
		Credits -= Delta;
		OnCreditsChanged.Broadcast(this, Credits, Delta);
		return true;
	}
	return false;
}

void ASPlayerState::SavePlayerState_Implementation(USSaveGame* SaveGame)
{
	if (SaveGame)
	{
		SaveGame->Credits = Credits;
	}
}

void ASPlayerState::LoadPlayerState_Implementation(USSaveGame* SaveGame)
{
	if (SaveGame)
	{
		Credits = SaveGame->Credits;
	}
}

int32 ASPlayerState::GetCredits()
{
	return Credits;
}

void ASPlayerState::OnRep_Credits(int32 OldCredits)
{
	// compare the old credits with the current credits
	OnCreditsChanged.Broadcast(this, Credits, Credits - OldCredits);
}

void ASPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ASPlayerState, Credits);
};
