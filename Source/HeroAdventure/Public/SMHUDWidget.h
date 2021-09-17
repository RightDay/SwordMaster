// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "HeroAdventure.h"
#include "Blueprint/UserWidget.h"
#include "SMHUDWidget.generated.h"

/**
 * 
 */
UCLASS()
class HEROADVENTURE_API USMHUDWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void BindCharacterStat(class USMCharacterStatComponent* CharacterStat);
	void BindPlayerState(class ASMPlayerState* PlayerState);

protected:
	virtual void NativeConstruct() override;
	void UpdateCharacterStat();
	void UpdatePlayerState();

private:
	TWeakObjectPtr<class USMCharacterStatComponent> CurrentCharacterStat;
	TWeakObjectPtr<class ASMPlayerState> CurrentPlayerState;

	UPROPERTY()
	class UProgressBar* HPBar;

	UPROPERTY()
	class UProgressBar* ExpBar;

	UPROPERTY()
	class UTextBlock* PlayerName;

	UPROPERTY()
	class UTextBlock* PlayerLevel;

	UPROPERTY()
	class UTextBlock* CurrentScore;

	UPROPERTY()
	class UTextBlock* HighScore;
};
