// Fill out your copyright notice in the Description page of Project Settings.


#include "SAction_Pickup.h"

#include "SActionComponent.h"

void ASAction_Pickup::Interact_Implementation(APawn* InstigatorPawn)
{
	if (USActionComponent* ActionComponent = Cast<USActionComponent>(InstigatorPawn->GetComponentByClass(USActionComponent::StaticClass())))
	{
		if (!ActionComponent->GetAction(ActionToAdd))
		{
			ActionComponent->AddAction(InstigatorPawn, ActionToAdd);
			HideAndCooldownPickup();
		}
		else
		{
			FString DebugMsg = FString::Printf(TEXT("Action '%s' already known."), *GetNameSafe(ActionToAdd));
			GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, DebugMsg);
		}
	}
}

ASAction_Pickup::ASAction_Pickup()
{
}
