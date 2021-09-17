// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "HeroAdventure.h"
#include "SMGameplayWidget.h"
#include "SMGameplayResultWidget.generated.h"

/**
 * 
 */
UCLASS()
class HEROADVENTURE_API USMGameplayResultWidget : public USMGameplayWidget
{
	GENERATED_BODY()
	
public:
	void BindGameState(class ASMGameState* GameState);

protected:
	virtual void NativeConstruct() override;

private:
	TWeakObjectPtr<class ASMGameState> CurrentGameState;
};
