// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "HeroAdventure.h"
#include "GameFramework/Actor.h"
#include "SMItemBox.generated.h"

UCLASS()
class HEROADVENTURE_API ASMItemBox : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASMItemBox();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void PostInitializeComponents() override;

public:	
	UPROPERTY(VisibleAnywhere, Category = Box)
	UBoxComponent* Trigger;

	UPROPERTY(VisibleAnywhere, Category = Box)
	UStaticMeshComponent* Box;

	UPROPERTY(VisibleAnywhere, Category = Effect)
	UParticleSystemComponent* Effect;

	UPROPERTY(EditInstanceOnly, Category = Box)
	TSubclassOf<class ASMWeapon> WeaponItemClass;

private:
	UFUNCTION()
	void OnCharacterOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnEffectFinished(class UParticleSystemComponent* PSystem);
};
