// Fill out your copyright notice in the Description page of Project Settings.


#include "SMUIPlayerController.h"
#include "Blueprint/UserWidget.h"

void ASMUIPlayerController::BeginPlay()
{
	Super::BeginPlay();

	SMCHECK(nullptr != UIWidgetClass);

	UIWidgetInstance = CreateWidget<UUserWidget>(this, UIWidgetClass);
	SMCHECK(nullptr != UIWidgetInstance);

	UIWidgetInstance->AddToViewport();

	FInputModeUIOnly Mode;
	Mode.SetWidgetToFocus(UIWidgetInstance->GetCachedWidget());
	SetInputMode(Mode);
	bShowMouseCursor = true;
}