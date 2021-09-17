// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "HeroAdventure.h"
#include "GameFramework/PlayerState.h"
#include "SMPlayerState.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnPlayerStateChangedDelegate);

/**
 * 
 */
UCLASS()
class HEROADVENTURE_API ASMPlayerState : public APlayerState
{
	GENERATED_BODY()
	
public:
	ASMPlayerState();
	
	void InitPlayerData();
	void SavePlayerData();

	int32 GetGameScore() const;
	int32 GetGameHighScore() const;
	int32 GetCharacterLevel() const;
	int32 GetCharacterIndex() const;

	FString SaveSlotName;

	float GetExpRatio() const;
	bool AddExp(int32 IncomeExp);
	void AddGameScore();

	FOnPlayerStateChangedDelegate OnPlayerStateChanged;

protected:
	UPROPERTY(Transient)
	int32 GameScore;

	UPROPERTY(Transient)
	int32 GameHighScore;

	UPROPERTY(Transient)
	int32 CharacterLevel;

	UPROPERTY(Transient)
	int32 Exp;

	UPROPERTY(Transient)
	int32 CharacterIndex;

private:
	void SetCharacterLevel(int32 NewCharacterLevel);
	struct FSMCharacterData* CurrentStatData;
};
