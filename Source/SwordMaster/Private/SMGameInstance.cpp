// Fill out your copyright notice in the Description page of Project Settings.

#include "SMGameInstance.h"

USMGameInstance::USMGameInstance()
{
	FString CharacterDataPath = TEXT("DataTable'/Game/GameData/SMCharacterData.SMCharacterData'");

	static ConstructorHelpers::FObjectFinder<UDataTable> DT_SMCharacter(*CharacterDataPath);
	SMCHECK(DT_SMCharacter.Succeeded());
	SMCharacterTable = DT_SMCharacter.Object;
	SMCHECK(SMCharacterTable->GetRowMap().Num() > 0);
}

void USMGameInstance::Init()
{
	Super::Init();
	SMLOG(Warning, TEXT("DropExp of Level 20 SMCharacter : %d"), GetSMCharacterData(20)->DropExp);
}

FSMCharacterData* USMGameInstance::GetSMCharacterData(int32 Level)
{
	return SMCharacterTable->FindRow<FSMCharacterData>(*FString::FromInt(Level), TEXT(""));
}
