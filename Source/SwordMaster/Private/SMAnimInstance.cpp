// Fill out your copyright notice in the Description page of Project Settings.


#include "SMAnimInstance.h"

USMAnimInstance::USMAnimInstance()
{
    CurrentPawnSpeed = 0.0f;
    IsInAir = false;
    IsDead = false;
    static ConstructorHelpers::FObjectFinder<UAnimMontage> ATTACK_MONTAGE(TEXT("/Game/MyAssets/Animations/SK_Mannequin_Skeleton_Montage.SK_Mannequin_Skeleton_Montage"));
    
    if (ATTACK_MONTAGE.Succeeded())
    {
        AttackMontage = ATTACK_MONTAGE.Object;
    }
}

void USMAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
    Super::NativeUpdateAnimation(DeltaSeconds);

    auto Pawn = TryGetPawnOwner();
    if (!::IsValid(Pawn)) return;

    if (!IsDead)
    {
        CurrentPawnSpeed = Pawn->GetVelocity().Size();
        auto Character = Cast<ACharacter>(Pawn);
        if (Character)
        {
            IsInAir = Character->GetMovementComponent()->IsFalling();
        }
    }
}

void USMAnimInstance::PlayAttackMontage()
{
    SMCHECK(!IsDead);
    Montage_Play(AttackMontage, 1.0f);
}

void USMAnimInstance::JumpToAttackMontageSection(int32 NewSection)
{
    SMCHECK(!IsDead);
    SMCHECK(Montage_IsPlaying(AttackMontage));
    Montage_JumpToSection(GetAttackMontageSectionName(NewSection), AttackMontage);
}

void USMAnimInstance::AnimNotify_AttackHitCheck()
{
    OnAttackHitCheck.Broadcast();
}

void USMAnimInstance::AnimNotify_NextAttackCheck()
{
    OnNextAttackCheck.Broadcast();
}

FName USMAnimInstance::GetAttackMontageSectionName(int32 Section)
{
    SMCHECK(FMath::IsWithinInclusive<int32>(Section, 1, 4), NAME_None);
    return FName(*FString::Printf(TEXT("Attack%d"), Section));
}
