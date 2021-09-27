// Fill out your copyright notice in the Description page of Project Settings.

#include "SMCharacterStatComponent.h"
#include "SMGameInstance.h"


// Sets default values for this component's properties
USMCharacterStatComponent::USMCharacterStatComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
	bWantsInitializeComponent = true;

	Level = 1;
}

// Called when the game starts
void USMCharacterStatComponent::BeginPlay()
{
	Super::BeginPlay();
	SetNewLevel(Level);
}

void USMCharacterStatComponent::InitializeComponent()
{
	Super::InitializeComponent();
}

void USMCharacterStatComponent::SetNewLevel(int32 NewLevel)
{
	auto SMGameInstance = Cast<USMGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

	SMCHECK(nullptr != SMGameInstance);
	CurrentStatData = SMGameInstance->GetSMCharacterData(NewLevel);
	if (nullptr != CurrentStatData)
	{
		Level = NewLevel;
		SetHP(CurrentStatData->MaxHP);
	}
	else
	{
		SMLOG(Error, TEXT("Level (%d) data doesn't exist"), NewLevel);
	}
}

void USMCharacterStatComponent::SetDamage(float NewDamage)
{
	SMCHECK(nullptr != CurrentStatData);
	SetHP(FMath::Clamp<float>(CurrentHP - NewDamage, 0.0f, CurrentStatData->MaxHP));
}

void USMCharacterStatComponent::SetHP(float NewHP)
{
	CurrentHP = NewHP;
	OnHPChanged.Broadcast();
	if (CurrentHP < KINDA_SMALL_NUMBER)
	{
		CurrentHP = 0.0f;
		OnHPIsZero.Broadcast();
	}
}

float USMCharacterStatComponent::GetAttack() const
{
	SMLOG(Warning, TEXT("GetAttack"));
	SMCHECK(nullptr != CurrentStatData, 0.0f);
	return CurrentStatData->Attack;
}

float USMCharacterStatComponent::GetHPRatio() const
{
	SMLOG(Warning, TEXT("GetHPRatio"));
	SMCHECK(nullptr != CurrentStatData, 0.0f);

	return (CurrentStatData->MaxHP < KINDA_SMALL_NUMBER) ? 0.0f : (CurrentHP / CurrentStatData->MaxHP);
}

int32 USMCharacterStatComponent::GetDropExp() const
{
	return CurrentStatData->DropExp;
}
