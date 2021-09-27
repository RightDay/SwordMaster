// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "SwordMaster.h"
#include "SMGameplayWidget.h"
#include "SMGameplayResultWidget.generated.h"

/**
 * 
 */
UCLASS()
class SWORDMASTER_API USMGameplayResultWidget : public USMGameplayWidget
{
	GENERATED_BODY()
	
public:
	void BindGameState(class ASMGameState* GameState);

protected:
	virtual void NativeConstruct() override;

private:
	TWeakObjectPtr<class ASMGameState> CurrentGameState;
};
