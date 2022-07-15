// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/SAICharacter.h"

#include "AIController.h"
#include "BrainComponent.h"
#include "DrawDebugHelpers.h"
#include "SActionComponent.h"
#include "SWorldUserWidget.h"
#include "SAttributeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Blueprint/UserWidget.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Perception/PawnSensingComponent.h"

// Sets default values
ASAICharacter::ASAICharacter()
{
	PawnSensingComp = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("PawnSensingComponent"));
	AttributeComponent = CreateDefaultSubobject<USAttributeComponent>("AttributeComponent");
	ActionComponent = CreateDefaultSubobject<USActionComponent>("ActionComponent");

	//GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_WorldDynamic, ECR_Ignore);
	GetMesh()->SetGenerateOverlapEvents(true);
	TimeToHitParamName = "TimeToHit";
}

void ASAICharacter::SetTargetActor(AActor* NewTarget)
{
	AAIController* AIC = Cast<AAIController>(GetController());
	if (AIC)
	{
		AIC->GetBlackboardComponent()->SetValueAsObject("TargetActor", NewTarget);
	}
}

AActor* ASAICharacter::GetTargetActor() const
{
	if (AAIController* AIC = Cast<AAIController>(GetController()))
	{
		return Cast<AActor>(AIC->GetBlackboardComponent()->GetValueAsObject("TargetActor"));
	}
	return nullptr;
}

void ASAICharacter::OnPawnSeen(APawn* Pawn)
{
	if (GetTargetActor() != Pawn)
	{
		SetTargetActor(Pawn);
		//DrawDebugString(GetWorld(), GetActorLocation(), TEXT("PLAYER SPOTTED"), nullptr, FColor::White, 4, true);

		if (!ActivePawnSeen)
		{
			MulticastPawnSeen();
		}
	}
}

void ASAICharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	PawnSensingComp->OnSeePawn.AddUniqueDynamic(this, &ThisClass::OnPawnSeen);
	AttributeComponent->OnHealthChanged.AddUniqueDynamic(this, &ThisClass::OnHealthChanged);
}

// Called to bind functionality to input
void ASAICharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void ASAICharacter::OnHealthChanged(AActor* InstigatorActor, USAttributeComponent* OwningComp, float NewHealth, float Delta)
{
	if (Delta < 0)
	{
		if (InstigatorActor != this)
		{
			SetTargetActor(InstigatorActor);
			GetMesh()->SetScalarParameterValueOnMaterials(TimeToHitParamName, GetWorld()->TimeSeconds);
		}

		if (!ActiveHealthBar)
		{
			ActiveHealthBar = CreateWidget<USWorldUserWidget>(GetWorld(), HealthBarWidgetClass);
			if (ActiveHealthBar)
			{
				ActiveHealthBar->AttachedActor = this;
				ActiveHealthBar->AddToViewport();
			}
		}

		if (NewHealth <= 0.0f)
		{
			// stop BT
			if (AAIController* AIC = Cast<AAIController>(GetController()))
			{
				AIC->GetBrainComponent()->StopLogic("Died");
			}
			
			//ragdoll
			GetMesh()->SetAllBodiesSimulatePhysics(true);
			GetMesh()->SetCollisionProfileName("Ragdoll");

			GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
			GetCharacterMovement()->DisableMovement();

			//set lifespan
			SetLifeSpan(10);
		}
	}
}

void ASAICharacter::MulticastPawnSeen_Implementation()
{
	ActivePawnSeen = CreateWidget<USWorldUserWidget>(GetWorld(), FoundPlayerWidgetClass);
	if (ActivePawnSeen)
	{
		ActivePawnSeen->AttachedActor = this;
		ActivePawnSeen->AddToViewport(10);
	}
}
