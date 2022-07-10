// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/SBTTask_HealSelf.h"

#include "AIController.h"
#include "SAttributeComponent.h"

EBTNodeResult::Type USBTTask_HealSelf::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if (APawn* MyPawn = Cast<APawn>(OwnerComp.GetAIOwner()->GetPawn()))
	{
		if (USAttributeComponent* AttributeComponent = USAttributeComponent::GetAttributes(MyPawn))
		{
			AttributeComponent->ApplyHealthChange(MyPawn, AttributeComponent->GetHealthMax());
			return EBTNodeResult::Succeeded;
		}
		else
		{
			return EBTNodeResult::Failed;
		}
	}

	return EBTNodeResult::Failed;
}
