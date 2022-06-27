// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SDashProjectile.h"
#include "SInteractionComponent.h"
#include "SMagicProjectile.h"
#include "GameFramework/Character.h"
#include "SCharacter.generated.h"

class USActionComponent;
class UCameraComponent;
class USpringArmComponent;
class USInteractionComponent;
class UAnimMontage;
class USAttributeComponent;

UCLASS()
class ACTIONROGUELIKE_API ASCharacter : public ACharacter
{
	GENERATED_BODY()

protected:

	UPROPERTY(EditDefaultsOnly, Category = "Attack")
	FName TimeToHitParamName;

	FTimerHandle TimerHandle_PrimaryAttack;

	void ShootProjectile(TSubclassOf<AActor> ProjectileClass);

public:
	// Sets default values for this character's properties
	ASCharacter();

protected:

	UPROPERTY(VisibleAnywhere)
	USpringArmComponent* SpringArmComp;

	UPROPERTY(VisibleAnywhere)
	UCameraComponent* CameraComp;

	UPROPERTY(VisibleAnywhere)
	USInteractionComponent* InteractionComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category= "Components")
	USAttributeComponent* AttributeComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category= "Components")
	USActionComponent* ActionComp; 

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void MoveForward(float Value);
	void MoveRight(float Value);

	void SprintStart();
	void SprintStop();

	void PrimaryAttack();

	void BlackHoleAttack();

	void Dash();

	void PrimaryInteract();

	void StartAttackEffects();

	UFUNCTION()
	void OnHealthChanged(AActor* InstigatorActor, USAttributeComponent* OwningComp, float NewHealth, float Delta);

	virtual void PostInitializeComponents() override;
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(Exec)
	void HealSelf(float Amount = 100);
	
	virtual FVector GetPawnViewLocation() const override;
};
