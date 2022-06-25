// Fill out your copyright notice in the Description page of Project Settings.


#include "SDashProjectile.h"

#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"

void ASDashProjectile::Explode_Implementation()
{
	GetWorldTimerManager().ClearTimer(TeleportHandle);

	UGameplayStatics::SpawnEmitterAtLocation(this, ImpactVFX, GetActorLocation(), GetActorRotation());

	UGameplayStatics::PlaySoundAtLocation(this, ImpactSound, GetActorLocation());

	EffectComp->DeactivateSystem();

	MovementComp->StopMovementImmediately();
	SetActorEnableCollision(false);

	FTimerHandle DelayedTeleportHandle;
	GetWorldTimerManager().SetTimer(DelayedTeleportHandle, this, &ThisClass::TeleportInstigator, TeleportDelay);
}

void ASDashProjectile::TeleportInstigator()
{
	AActor* TeleportActor = GetInstigator();

	if(ensure(TeleportActor))
	{
		TeleportActor->TeleportTo(GetActorLocation(), TeleportActor->GetActorRotation(), false, false);

		APawn* InstigatorPawn = Cast<APawn>(TeleportActor);
		APlayerController* PC = Cast<APlayerController>(InstigatorPawn->GetController());
		if(PC && PC->IsLocalController())
		{
			PC->ClientPlayCameraShake(ImpactShake);
		}
	}
}

void ASDashProjectile::BeginPlay()
{
	Super::BeginPlay();

	GetWorldTimerManager().SetTimer(TeleportHandle, this, &ThisClass::Explode, DetonateDelay);
}

ASDashProjectile::ASDashProjectile()
{
	TeleportDelay = 0.2f;
	DetonateDelay = 0.2f;
}
