// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "HeroAdventure.h"
#include "GameFramework/GameModeBase.h"
#include "SMGameMode.generated.h"

/**
 * 
 */
UCLASS()
class HEROADVENTURE_API ASMGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ASMGameMode();

	virtual void PostInitializeComponents() override;
	virtual void PostLogin(APlayerController* NewPlayer) override;
	void AddScore(class ASMPlayerController* ScoredPlayer);
	int32 GetScore() const;

private:
	UPROPERTY()
	class ASMGameState* SMGameState;

	UPROPERTY()
	int32 ScoreToClear;
};
