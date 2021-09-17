// Fill out your copyright notice in the Description page of Project Settings.


#include "SMPlayerController.h"
#include "SMHUDWidget.h"
#include "SMPlayerState.h"
#include "SMCharacter.h"
#include "SMGameplayWidget.h"
#include "SMGameplayResultWidget.h"
#include "SMGameState.h"

ASMPlayerController::ASMPlayerController()
{
	static ConstructorHelpers::FClassFinder<USMHUDWidget> UI_HUD_C(TEXT("WidgetBlueprint'/Game/Book/UI/UI_HUD.UI_HUD_C'"));
	if (UI_HUD_C.Succeeded())
	{
		HUDWidgetClass = UI_HUD_C.Class;
	}

	static ConstructorHelpers::FClassFinder<USMGameplayWidget> UI_MENU_C(TEXT("/Game/Book/UI/UI_Menu.UI_Menu_C"));
	if (UI_MENU_C.Succeeded())
	{
		MenuWidgetClass = UI_MENU_C.Class;
	}

	static ConstructorHelpers::FClassFinder<USMGameplayResultWidget> UI_RESULT_C(TEXT("/Game/Book/UI/UI_Result.UI_Result_C"));
	if (UI_RESULT_C.Succeeded())
	{
		ResultWidgetClass = UI_RESULT_C.Class;
	}
}

void ASMPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	InputComponent->BindAction(TEXT("GamePause"), EInputEvent::IE_Pressed, this, &ASMPlayerController::OnGamePause);
}

void ASMPlayerController::BeginPlay()
{
	Super::BeginPlay();

	ChangeInputMode(true);

	FInputModeGameOnly InputMode;
	SetInputMode(InputMode);

	HUDWidget = CreateWidget<USMHUDWidget>(this, HUDWidgetClass);
	ABCHECK(nullptr != HUDWidget);
	HUDWidget->AddToViewport(1);

	ResultWidget = CreateWidget<USMGameplayResultWidget>(this, ResultWidgetClass);
	ABCHECK(nullptr != ResultWidget);

	SMPlayerState = Cast<ASMPlayerState>(PlayerState);
	ABCHECK(nullptr != SMPlayerState);
	HUDWidget->BindPlayerState(SMPlayerState);
	SMPlayerState->OnPlayerStateChanged.Broadcast();
}

void ASMPlayerController::OnGamePause()
{
	MenuWidget = CreateWidget<USMGameplayWidget>(this, MenuWidgetClass);
	ABCHECK(nullptr != MenuWidget);
	MenuWidget->AddToViewport(3);

	SetPause(true);
	ChangeInputMode(false);
}

USMHUDWidget* ASMPlayerController::GetHUDWidget() const
{
	return HUDWidget;
}

void ASMPlayerController::NPCKill(ASMCharacter* KilledNPC) const
{
	SMPlayerState->AddExp(KilledNPC->GetExp());
}

void ASMPlayerController::AddGameScore() const
{
	SMPlayerState->AddGameScore();
}

void ASMPlayerController::ChangeInputMode(bool bGameMode)
{
	if (bGameMode)
	{
		SetInputMode(GameInputMode);
		bShowMouseCursor = false;
	}
	else
	{
		SetInputMode(UIInputMode);
		bShowMouseCursor = true;
	}
}

void ASMPlayerController::ShowResultUI()
{
	auto SMGameState = Cast<ASMGameState>(UGameplayStatics::GetGameState(this));
	ABCHECK(nullptr != SMGameState);
	ResultWidget->BindGameState(SMGameState);

	ResultWidget->AddToViewport();
	ChangeInputMode(false);
}

void ASMPlayerController::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	ABLOG_S(Warning);
}

void ASMPlayerController::OnPossess(APawn* aPawn)
{
	ABLOG_S(Warning);
	Super::OnPossess(aPawn);
}
