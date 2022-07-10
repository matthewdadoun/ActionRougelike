// Fill out your copyright notice in the Description page of Project Settings.


#include "SPlayerState.h"

void ASPlayerState::AddCredits(float Delta)
{
	Credits += Delta;

	OnCreditsChanged.Broadcast(this, Credits, Delta);
}

bool ASPlayerState::RemoveCredits(float Delta)
{
	if(!ensure(Delta > 0))
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
