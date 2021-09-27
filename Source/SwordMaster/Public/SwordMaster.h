// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EngineMinimal.h"

UENUM(BlueprintType)
enum class ECharacterState : uint8
{
	PREINIT,
	LOADING,
	READY,
	DEAD
};

DECLARE_LOG_CATEGORY_EXTERN(SwordMaster, Log, All);
#define SMLOG_CALLINFO (FString(__FUNCTION__) + TEXT("(") + FString::FromInt(__LINE__) + TEXT(")"))
#define SMLOG_S(Verbosity) UE_LOG(SwordMaster, Verbosity, TEXT("%s"), *SMLOG_CALLINFO)
#define SMLOG(Verbosity, Format, ...) UE_LOG(SwordMaster, Verbosity, TEXT("%s%s"), *SMLOG_CALLINFO, *FString::Printf(Format, ##__VA_ARGS__))
#define SMCHECK(Expr, ...) {if(!(Expr)) {SMLOG(Error, TEXT("ASSERTION : %s"), TEXT("'"#Expr"'")); return __VA_ARGS__;}}