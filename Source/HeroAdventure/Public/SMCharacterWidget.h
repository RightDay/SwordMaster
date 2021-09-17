// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "HeroAdventure.h"
#include "Blueprint/UserWidget.h"
#include "SMCharacterWidget.generated.h"

/**
 *
 */
UCLASS()
class HEROADVENTURE_API USMCharacterWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void BindCharacterStat(class USMCharacterStatComponent* NewCharacterStat);

protected:
	virtual void NativeConstruct() override;
	void UpdateHPWidget();

private:
	TWeakObjectPtr<class USMCharacterStatComponent> CurrentCharacterStat;

	UPROPERTY()
	class UProgressBar* HPProgressBar;
};
