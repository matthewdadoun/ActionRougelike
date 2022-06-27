// Fill out your copyright notice in the Description page of Project Settings.


#include "SAction.h"

void USAction::StartAction_Implementation(AActor* Instigator)
{
	UE_LOG(LogTemp, Log, TEXT("Running: %s"), *GetNameSafe(this));

	USActionComponent* OwningComp = GetOwningComponent();
	OwningComp->ActiveGameplayTags.AppendTags(GrantsTags);

	bIsRunning = true;
}

void USAction::StopAction_Implementation(AActor* Instigator)
{
	UE_LOG(LogTemp, Log, TEXT("Stopping: %s"), *GetNameSafe(this));

	ensureAlways(bIsRunning);

	USActionComponent* OwningComp = GetOwningComponent();
	OwningComp->ActiveGameplayTags.RemoveTags(GrantsTags);

	bIsRunning = false;
}

USActionComponent* USAction::GetOwningComponent() const
{
	return Cast<USActionComponent>(GetOuter());
}

bool USAction::CanStart_Implementation(AActor* Instigator)
{
	if (IsRunning())
	{
		return false;
	}

	USActionComponent* OwningComp = GetOwningComponent();
	if (OwningComp->ActiveGameplayTags.HasAny(BlockedTags))
	{
		return false;
	}
	return true;
}

UWorld* USAction::GetWorld() const
{
	if (UActorComponent* Comp = Cast<UActorComponent>(GetOuter()))
	{
		return Comp->GetWorld();
	}
	return nullptr;
}
