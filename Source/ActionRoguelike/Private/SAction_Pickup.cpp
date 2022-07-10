// Fill out your copyright notice in the Description page of Project Settings.


#include "SAction_Pickup.h"

#include "SActionComponent.h"

void ASAction_Pickup::AddAction(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (USActionComponent* ActionComponent = Cast<USActionComponent>(OtherActor->GetComponentByClass(USActionComponent::StaticClass())))
	{
		if (!ActionComponent->GetAction(ActionToAdd))
		{
			ActionComponent->AddAction(OtherActor, ActionToAdd);
			HidePickup();
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
	ActionMeshComp = CreateDefaultSubobject<UStaticMeshComponent>("ActionMeshComp");
	RootComponent = ActionMeshComp;

	ActionMeshComp->OnComponentBeginOverlap.AddUniqueDynamic(this, &ThisClass::AddAction);
}
