// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "SwordMaster.h"
#include "GameFramework/SaveGame.h"
#include "SMSaveGame.generated.h"

/**
 * 
 */
UCLASS()
class SWORDMASTER_API USMSaveGame : public USaveGame
{
	GENERATED_BODY()
	
public:
	USMSaveGame();

	UPROPERTY()
	int32 Level;

	UPROPERTY()
	int32 Exp;

	UPROPERTY()
	FString PlayerName;

	UPROPERTY()
	int32 HighScore;

	UPROPERTY()
	int32 CharacterIndex;
};
