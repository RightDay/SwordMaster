// Fill out your copyright notice in the Description page of Project Settings.


#include "SMGameState.h"

ASMGameState::ASMGameState()
{
	TotalGameScore = 0;
	bGameCleared = false;
}

int32 ASMGameState::GetTotalGameScore() const
{
	return TotalGameScore;
}

void ASMGameState::AddGameScore()
{
	TotalGameScore++;
}

void ASMGameState::SetGameCleared()
{
	bGameCleared = true;
}

bool ASMGameState::IsGameCleared() const
{
	return bGameCleared;
}
