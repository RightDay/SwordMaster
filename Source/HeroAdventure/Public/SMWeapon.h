// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "HeroAdventure.h"
#include "GameFramework/Actor.h"
#include "SMWeapon.generated.h"

UCLASS()
class HEROADVENTURE_API ASMWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASMWeapon();

	float GetAttackRange() const;
	float GetAttackDamage() const;
	float GetAttackModifer() const;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	UPROPERTY(VisibleAnywhere, Category = Weapon)
	USkeletalMeshComponent* Weapon;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Attack)
	float AttackRange;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Attack)
	float AttackDamageMin;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Attack)
	float AttackDamageMax;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Attack)
	float AttackModifierMin;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Attack)
	float AttackModifierMax;

	UPROPERTY(Transient, VisibleInstanceOnly, BlueprintReadOnly, Category = Attack)
	float AttackDamage;

	UPROPERTY(Transient, VisibleInstanceOnly, BlueprintReadOnly, Category = Attack)
	float AttackModifier;
};
