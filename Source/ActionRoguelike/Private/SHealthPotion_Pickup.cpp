// Fill out your copyright notice in the Description page of Project Settings.


#include "SHealthPotion_Pickup.h"

#include "SPlayerState.h"
#include "SAttributeComponent.h"
#include "Kismet/GameplayStatics.h"

#define LOCTEXT_NAMESPACE "InteractableActors"

//void ASHealthPotion_Pickup::RefillHealth(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
//                                         const FHitResult& SweepResult)
//{
//	
//}

ASHealthPotion_Pickup::ASHealthPotion_Pickup()
{
	CreditCost = 5;
}

void ASHealthPotion_Pickup::Interact_Implementation(APawn* InstigatorPawn)
{
	Super::Interact_Implementation(InstigatorPawn);

	if (!ensure(InstigatorPawn))
	{
		return;
	}

	if (APawn* Pawn = Cast<APawn>(InstigatorPawn))
	{
		if (ASPlayerState* PS = Cast<ASPlayerState>(Pawn->GetPlayerState()))
		{
			USAttributeComponent* AttributeComp = Cast<USAttributeComponent>(Pawn->GetComponentByClass(USAttributeComponent::StaticClass()));

			if (!AttributeComp->IsFullHealth())
			{
				if (PS->RemoveCredits(CreditCost))
				{
					if (AttributeComp->ApplyHealthChange(this, AttributeComp->GetHealthMax()))
					{
						HideAndCooldownPickup();
					}
				}
			}
		}
	}
}

FText ASHealthPotion_Pickup::GetInteractText_Implementation(APawn* InstigatorPawn)
{
	USAttributeComponent* AttributeComp = Cast<USAttributeComponent>(InstigatorPawn->GetComponentByClass(USAttributeComponent::StaticClass()));
	if (AttributeComp && AttributeComp->IsFullHealth())
	{
		//NSLOCTEXT means NameSpaceLocText, which can be defined as NAMESPACE_LOCTEXT which you don't need to specify a namespace within that context :)
		return LOCTEXT("HealthPotion_FullHealthWarning", "Already at full health");
	}

	return FText::Format(LOCTEXT("HealthPotion_InteractMessage", "Cost {0} Credits. Restores health to maximum"), CreditCost);
}

#undef LOCTEXT_NAMESPACE
