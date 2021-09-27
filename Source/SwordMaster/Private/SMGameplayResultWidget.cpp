// Fill out your copyright notice in the Description page of Project Settings.


#include "SMGameplayResultWidget.h"
#include "Components/TextBlock.h"
#include "SMGameState.h"


void USMGameplayResultWidget::BindGameState(class ASMGameState* GameState)
{
	SMCHECK(nullptr != GameState);
	CurrentGameState = GameState;
}

void USMGameplayResultWidget::NativeConstruct()
{
	Super::NativeConstruct();

	SMCHECK(CurrentGameState.IsValid());

	auto Result = Cast<UTextBlock>(GetWidgetFromName(TEXT("txtResult")));
	SMCHECK(nullptr != Result);
	Result->SetText(FText::FromString(CurrentGameState->IsGameCleared() ? TEXT("Mission Complete") : TEXT("Mission Failed")));

	auto TotalScore = Cast<UTextBlock>(GetWidgetFromName(TEXT("txtTotalScore")));
	SMCHECK(nullptr != TotalScore);
	TotalScore->SetText(FText::FromString(FString::FromInt(CurrentGameState->GetTotalGameScore())));
}

