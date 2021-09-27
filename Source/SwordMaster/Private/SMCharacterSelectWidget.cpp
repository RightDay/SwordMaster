// Fill out your copyright notice in the Description page of Project Settings.


#include "SMCharacterSelectWidget.h"
#include "ABCharacterSetting.h"
#include "SMGameInstance.h"
#include "EngineUtils.h"
#include "Animation/SkeletalMeshActor.h"
#include "Components/Button.h"
#include "Components/EditableTextBox.h"
#include "SMSaveGame.h"
#include "SMPlayerState.h"

void USMCharacterSelectWidget::NextCharacter(bool bForward)
{
	bForward ? CurrentIndex++ : CurrentIndex--;

	if (CurrentIndex == -1) CurrentIndex = MaxIndex - 1;
	if (CurrentIndex == MaxIndex) CurrentIndex = 0;

	auto CharacterSetting = GetDefault<UABCharacterSetting>();
	auto AssetRef = CharacterSetting->CharacterAssets[CurrentIndex];

	auto SMGameInstance = GetWorld()->GetGameInstance<USMGameInstance>();
	SMCHECK(nullptr != SMGameInstance);
	SMCHECK(TargetComponent.IsValid());

	USkeletalMesh* Asset = SMGameInstance->StreamableManager.LoadSynchronous<USkeletalMesh>(AssetRef);
	if (nullptr != Asset)
	{
		TargetComponent->SetSkeletalMesh(Asset);
	}
}

void USMCharacterSelectWidget::NativeConstruct()
{
	Super::NativeConstruct();

	CurrentIndex = 0;
	auto CharacterSetting = GetDefault<UABCharacterSetting>();
	MaxIndex = CharacterSetting->CharacterAssets.Num();

	for (TActorIterator<ASkeletalMeshActor> It(GetWorld()); It; ++It)
	{
		TargetComponent = It->GetSkeletalMeshComponent();
		break;
	}

	PrevButton = Cast<UButton>(GetWidgetFromName(TEXT("btnPrev")));
	SMCHECK(nullptr != PrevButton);

	NextButton = Cast<UButton>(GetWidgetFromName(TEXT("btnNext")));
	SMCHECK(nullptr != NextButton);

	TextBox = Cast<UEditableTextBox>(GetWidgetFromName(TEXT("edtPlayerName")));
	SMCHECK(nullptr != TextBox);

	ConfirmButton = Cast<UButton>(GetWidgetFromName(TEXT("btnConfirm")));
	SMCHECK(nullptr != ConfirmButton);

	PrevButton->OnClicked.AddDynamic(this, &USMCharacterSelectWidget::OnPrevClicked);
	NextButton->OnClicked.AddDynamic(this, &USMCharacterSelectWidget::OnNextClicked);
	ConfirmButton->OnClicked.AddDynamic(this, &USMCharacterSelectWidget::OnConfirmClicked);
}

void USMCharacterSelectWidget::OnPrevClicked()
{
	NextCharacter(false);
}

void USMCharacterSelectWidget::OnNextClicked()
{
	NextCharacter(true);
}

void USMCharacterSelectWidget::OnConfirmClicked()
{
	FString CharacterName = TextBox->GetText().ToString();
	if (CharacterName.Len() <= 0 || CharacterName.Len() > 10) return;

	USMSaveGame* NewPlayerData = NewObject<USMSaveGame>();
	NewPlayerData->PlayerName = CharacterName;
	NewPlayerData->Level = 1;
	NewPlayerData->Exp = 0;
	NewPlayerData->HighScore = 0;
	NewPlayerData->CharacterIndex = CurrentIndex;

	auto SMPlayerState = GetDefault<ASMPlayerState>();
	if (UGameplayStatics::SaveGameToSlot(NewPlayerData, SMPlayerState->SaveSlotName, 0))
	{
		UGameplayStatics::OpenLevel(GetWorld(), TEXT("Gameplay"));
	}
	else
	{
		SMLOG(Error, TEXT("SaveGame Error!"));
	}
}
