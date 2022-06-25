// Fill out your copyright notice in the Description page of Project Settings.


#include "SHealthPotion_Pickup.h"

#include "ActionRoguelike/SAttributeComponent.h"
#include "Kismet/GameplayStatics.h"

void ASHealthPotion_Pickup::RefillHealth(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
                                         const FHitResult& SweepResult)
{
	if (!ensure(OtherActor))
	{
		return;
	}

	if ((OtherActor == UGameplayStatics::GetPlayerPawn(this, 0)))
	{
		USAttributeComponent* AttributeComp = Cast<USAttributeComponent>(OtherActor->GetComponentByClass(USAttributeComponent::StaticClass()));

		if (!AttributeComp->IsFullHealth())
		{
			if (AttributeComp->ApplyHealthChange(this, AttributeComp->GetHealthMax()))
			{
				HidePickup();
			}
		}
	}
}

void ASHealthPotion_Pickup::BeginPlay()
{
	Super::BeginPlay();
}

ASHealthPotion_Pickup::ASHealthPotion_Pickup()
{
	PotionBottleMeshComp = CreateDefaultSubobject<UStaticMeshComponent>("PotionBottleMeshComp");
	PotionBottleMeshComp->SetupAttachment(RootComponent);

	PotionBottleMeshComp->OnComponentBeginOverlap.AddUniqueDynamic(this, &ThisClass::RefillHealth);
}

void ASHealthPotion_Pickup::Interact_Implementation(APawn* InstigatorPawn)
{
}
