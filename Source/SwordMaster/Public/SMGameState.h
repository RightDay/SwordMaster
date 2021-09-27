// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "SwordMaster.h"
#include "GameFramework/GameStateBase.h"
#include "SMGameState.generated.h"

/**
 * 
 */
UCLASS()
class SWORDMASTER_API ASMGameState : public AGameStateBase
{
	GENERATED_BODY()
	
public:
	ASMGameState();

public:
	int32 GetTotalGameScore() const;
	void AddGameScore();

	void SetGameCleared();
	bool IsGameCleared() const;

private:
	UPROPERTY(Transient)
	int32 TotalGameScore;

	UPROPERTY(Transient)
	bool bGameCleared;
};
