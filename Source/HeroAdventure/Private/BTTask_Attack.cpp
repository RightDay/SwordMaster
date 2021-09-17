// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_Attack.h"
#include "SMAIController.h"
#include "SMCharacter.h"

UBTTask_Attack::UBTTask_Attack()
{
	bNotifyTick = true;
	IsAttacking = false;
}

EBTNodeResult::Type UBTTask_Attack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	auto SMCharacter = Cast<ASMCharacter>(OwnerComp.GetAIOwner()->GetPawn());
	if (nullptr == SMCharacter)
		return EBTNodeResult::Failed;

	SMCharacter->Attack();
	IsAttacking = true;
	SMCharacter->OnAttackEnd.AddLambda([this]()->void {
		IsAttacking = false;
	});

	return EBTNodeResult::InProgress;
}

void UBTTask_Attack::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);
	if (!IsAttacking)
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}
}
