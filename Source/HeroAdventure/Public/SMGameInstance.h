// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "HeroAdventure.h"
#include "Engine/DataTable.h"
#include "Engine/GameInstance.h"
#include "Engine/StreamableManager.h"
#include "SMGameInstance.generated.h"

USTRUCT(BlueprintType)
struct FSMCharacterData : public FTableRowBase
{
	GENERATED_BODY()

public:
	FSMCharacterData() : Level(1), MaxHP(100.0f), Attack(10.0f), DropExp(10), NextExp(30) {}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	int32 Level;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	float MaxHP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	float Attack;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	int32 DropExp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	int32 NextExp;
};

/**
 * 
 */
UCLASS()
class HEROADVENTURE_API USMGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	USMGameInstance();

	virtual void Init() override;
	FSMCharacterData* GetSMCharacterData(int32 Level);

	FStreamableManager StreamableManager;

private:
	UPROPERTY()
	class UDataTable* SMCharacterTable;
};
