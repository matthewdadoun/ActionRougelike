// Fill out your copyright notice in the Description page of Project Settings.


#include "SHealthPotion_Pickup.h"

#include "SPlayerState.h"
#include "ActionRoguelike/SAttributeComponent.h"
#include "Kismet/GameplayStatics.h"

void ASHealthPotion_Pickup::RefillHealth(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
                                         const FHitResult& SweepResult)
{
	if (!ensure(OtherActor))
	{
		return;
	}

	if (APawn* Pawn = Cast<APawn>(OtherActor))
	{
		if (ASPlayerState* PS = Cast<ASPlayerState>(Pawn->GetPlayerState()))
		{
			USAttributeComponent* AttributeComp = Cast<USAttributeComponent>(Pawn->GetComponentByClass(USAttributeComponent::StaticClass()));

			if (!AttributeComp->IsFullHealth())
			{
				if (PS->RemoveCredits(1))
				{
					if (AttributeComp->ApplyHealthChange(this, AttributeComp->GetHealthMax()))
					{
						HidePickup();
					}
				}
			}
		}
	}
}

ASHealthPotion_Pickup::ASHealthPotion_Pickup()
{
	PotionBottleMeshComp = CreateDefaultSubobject<UStaticMeshComponent>("PotionBottleMeshComp");
	PotionBottleMeshComp->SetupAttachment(RootComponent);

	PotionBottleMeshComp->OnComponentBeginOverlap.AddUniqueDynamic(this, &ThisClass::RefillHealth);
}
