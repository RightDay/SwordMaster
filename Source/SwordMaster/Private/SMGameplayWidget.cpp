// Fill out your copyright notice in the Description page of Project Settings.


#include "SMGameplayWidget.h"
#include "Components/Button.h"
#include "SMPlayerController.h"

void USMGameplayWidget::NativeConstruct()
{
	Super::NativeConstruct();

	ResumeButton = Cast<UButton>(GetWidgetFromName(TEXT("btnResume")));
	if (nullptr != ResumeButton)
	{
		ResumeButton->OnClicked.AddDynamic(this, &USMGameplayWidget::OnResumeClicked);
	}

	ReturnToTitleButton = Cast<UButton>(GetWidgetFromName(TEXT("btnReturnToTitle")));
	if (nullptr != ReturnToTitleButton)
	{
		ReturnToTitleButton->OnClicked.AddDynamic(this, &USMGameplayWidget::OnReturnToTitleClicked);
	}

	RetryGameButton = Cast<UButton>(GetWidgetFromName(TEXT("btnRetryGame")));
	if (nullptr != RetryGameButton)
	{
		RetryGameButton->OnClicked.AddDynamic(this, &USMGameplayWidget::OnRetryGameClicked);
	}
}


void USMGameplayWidget::OnResumeClicked()
{
	auto SMPlayerController = Cast<ASMPlayerController>(GetOwningPlayer());
	SMCHECK(nullptr != SMPlayerController);

	RemoveFromParent();

	SMPlayerController->ChangeInputMode(true);
	SMPlayerController->SetPause(false);
}

void USMGameplayWidget::OnReturnToTitleClicked()
{
	UGameplayStatics::OpenLevel(GetWorld(), TEXT("Title"));
}

void USMGameplayWidget::OnRetryGameClicked()
{
	auto SMPlayerController = Cast<ASMPlayerController>(GetOwningPlayer());
	SMCHECK(nullptr != SMPlayerController)
	SMPlayerController->RestartLevel();
}
