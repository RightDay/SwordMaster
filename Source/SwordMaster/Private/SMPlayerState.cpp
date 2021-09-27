// Fill out your copyright notice in the Description page of Project Settings.


#include "SMPlayerState.h"
#include "SMGameInstance.h"
#include "SMSaveGame.h"

ASMPlayerState::ASMPlayerState()
{
	CharacterLevel = 1;
	GameScore = 0;
	GameHighScore = 0;
	Exp = 0;
	SaveSlotName = TEXT("Player1");

	CharacterIndex = 0;
}

void ASMPlayerState::InitPlayerData()
{
	auto SMSaveGame = Cast<USMSaveGame>(UGameplayStatics::LoadGameFromSlot(SaveSlotName, 0));
	if (nullptr == SMSaveGame)
	{
		SMSaveGame = GetMutableDefault<USMSaveGame>();
	}
	SetPlayerName(SMSaveGame->PlayerName);
	SetCharacterLevel(SMSaveGame->Level);
	GameScore = 0;
	GameHighScore = SMSaveGame->HighScore;
	Exp = SMSaveGame->Exp;
	CharacterIndex = SMSaveGame->CharacterIndex;
	SavePlayerData();
}

void ASMPlayerState::SavePlayerData()
{
	USMSaveGame* NewPlayerData = NewObject<USMSaveGame>();
	NewPlayerData->PlayerName = GetPlayerName();
	NewPlayerData->Level = CharacterLevel;
	NewPlayerData->Exp = Exp;
	NewPlayerData->HighScore = GameHighScore;
	NewPlayerData->CharacterIndex = CharacterIndex;

	if (!UGameplayStatics::SaveGameToSlot(NewPlayerData, SaveSlotName, 0))
	{
		SMLOG(Error, TEXT("SaveGame Error!"));
	}
}

int32 ASMPlayerState::GetGameScore() const
{
	return GameScore;
}

int32 ASMPlayerState::GetGameHighScore() const
{
	return GameHighScore;
}

int32 ASMPlayerState::GetCharacterLevel() const
{
	return CharacterLevel;
}

int32 ASMPlayerState::GetCharacterIndex() const
{
	return CharacterIndex;
}

float ASMPlayerState::GetExpRatio() const
{
	if (CurrentStatData->NextExp <= KINDA_SMALL_NUMBER)
		return 0.0f;

	float Result = (float)Exp / (float)CurrentStatData->NextExp;
	SMLOG(Warning, TEXT("Ratio : %f, Current : %d, Next : %d"), Result, Exp, CurrentStatData->NextExp);
	return Result;
}

bool ASMPlayerState::AddExp(int32 IncomeExp)
{
	if (CurrentStatData->NextExp == -1)
		return false;

	bool DidLevelUp = false;
	Exp = Exp + IncomeExp;
	if (Exp >= CurrentStatData->NextExp)
	{
		Exp -= CurrentStatData->NextExp;
		SetCharacterLevel(CharacterLevel + 1);
		DidLevelUp = true;
	}

	OnPlayerStateChanged.Broadcast();
	SavePlayerData();
	return DidLevelUp;
}

void ASMPlayerState::AddGameScore()
{
	GameScore++;
	if (GameScore >= GameHighScore)
	{
		GameHighScore = GameScore;
	}
	OnPlayerStateChanged.Broadcast();
	SavePlayerData();
}

void ASMPlayerState::SetCharacterLevel(int32 NewCharacterLevel)
{
	auto SMGameInstance = Cast<USMGameInstance>(GetGameInstance());
	SMCHECK(nullptr != SMGameInstance);

	CurrentStatData = SMGameInstance->GetSMCharacterData(NewCharacterLevel);
	SMCHECK(nullptr != CurrentStatData);

	CharacterLevel = NewCharacterLevel;
}
