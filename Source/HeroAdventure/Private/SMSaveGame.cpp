// Fill out your copyright notice in the Description page of Project Settings.


#include "SMSaveGame.h"

USMSaveGame::USMSaveGame()
{
	Level = 1;
	Exp = 0;
	PlayerName = TEXT("Guest");
	HighScore = 0;

	CharacterIndex = 0;
}