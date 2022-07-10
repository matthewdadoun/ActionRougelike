// Fill out your copyright notice in the Description page of Project Settings.


#include "SActionEffect_Thorns.h"

#include "SActionComponent.h"
#include "SGameplayFunctionLibrary.h"
#include "ActionRoguelike/SAttributeComponent.h"

USActionEffect_Thorns::USActionEffect_Thorns()
{
	ReflectFraction = 0.2f;

	// runs infinitely on the actor
	Duration = 0.0f;
	Period = 0.0f;
}

void USActionEffect_Thorns::StartAction_Implementation(AActor* Instigator)
{
	Super::StartAction_Implementation(Instigator);

	if (USAttributeComponent* AttributeComp = USAttributeComponent::GetAttributes(GetOwningComponent()->GetOwner()))
	{
		AttributeComp->OnHealthChanged.AddUniqueDynamic(this, &ThisClass::OnHealthChanged);
	}
}

void USActionEffect_Thorns::StopAction_Implementation(AActor* Instigator)
{
	Super::StopAction_Implementation(Instigator);

	if (USAttributeComponent* AttributeComp = USAttributeComponent::GetAttributes(GetOwningComponent()->GetOwner()))
	{
		AttributeComp->OnHealthChanged.RemoveDynamic(this, &ThisClass::OnHealthChanged);
	}
}

void USActionEffect_Thorns::OnHealthChanged(AActor* Instigator, USAttributeComponent* OwningComp, float NewHealth, float Delta)
{
	AActor* OwningActor = GetOwningComponent()->GetOwner();

	if (Delta < 0.0f && OwningActor != Instigator)
	{
		int32 ReflectedAmount = FMath::RoundToInt(Delta * ReflectFraction);
		if (ReflectedAmount == 0)
		{
			return;
		}

		ReflectedAmount = FMath::Abs(ReflectedAmount);

		USGameplayFunctionLibrary::ApplyDamage(OwningActor, Instigator, ReflectedAmount);
	}
}
