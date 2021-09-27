// Fill out your copyright notice in the Description page of Project Settings.


#include "SMGameMode.h"
#include "SMCharacter.h"
#include "SMPlayerController.h"
#include "SMPlayerState.h"
#include "SMGameState.h"

ASMGameMode::ASMGameMode()
{
	DefaultPawnClass = ASMCharacter::StaticClass();
	PlayerControllerClass = ASMPlayerController::StaticClass();
	PlayerStateClass = ASMPlayerState::StaticClass();
	GameStateClass = ASMGameState::StaticClass();

	ScoreToClear = 3;
}

void ASMGameMode::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	SMGameState = Cast<ASMGameState>(GameState);
}

void ASMGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);

	auto SMPlayerState = Cast<ASMPlayerState>(NewPlayer->PlayerState);
	SMCHECK(nullptr != SMPlayerState);
	SMPlayerState->InitPlayerData();
}

void ASMGameMode::AddScore(ASMPlayerController* ScoredPlayer)
{
	for (FConstPlayerControllerIterator It = GetWorld()->GetPlayerControllerIterator(); It; ++It)
	{
		const auto SMPlayerController = Cast<ASMPlayerController>(It->Get());
		if ((nullptr != SMPlayerController) && (ScoredPlayer == SMPlayerController))
		{
			SMPlayerController->AddGameScore();
			break;
		}
	}

	SMGameState->AddGameScore();

	if (GetScore() >= ScoreToClear)
	{
		SMGameState->SetGameCleared();

		for (FConstPawnIterator It = GetWorld()->GetPawnIterator(); It; ++It)
		{
			(*It)->TurnOff();
		}

		for (FConstPlayerControllerIterator It = GetWorld()->GetPlayerControllerIterator(); It; ++It)
		{
			const auto SMPlayerController = Cast<ASMPlayerController>(It->Get());
			if (nullptr != SMPlayerController)
			{
				SMPlayerController->ShowResultUI();
			}
		}
	}
}

int32 ASMGameMode::GetScore() const
{
	return SMGameState->GetTotalGameScore();
}
