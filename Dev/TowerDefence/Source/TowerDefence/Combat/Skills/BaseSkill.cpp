// Fill out your copyright notice in the Description page of Project Settings.

#include "BaseSkill.h"
#include "Engine/World.h"
#include "Engine/Public/TimerManager.h"
#include "Engine.h"

void UBaseSkill::Activate(UWorld* World, APawn* Instigator)
{
	if (GEngine) GEngine->AddOnScreenDebugMessage(2, 10.f, FColor::Blue, FString::Printf(TEXT("BaseSkill.cpp::Activate --> Activated a new skill!")));
	m_World = World;
	m_Instigator = Instigator;

	//Tell the system the skill is being channeled
	m_SkillState = ESkillState::SS_IsBeingChanneled;

	//Tell the timer to start channeling, if it completes execute the skill
	if (m_World)
		m_World->GetTimerManager().SetTimer(m_ChannelingTimerHandle, this, &UBaseSkill::Execute, m_ChannelingDuration);
	else
		if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, FString::Printf(TEXT("BaseSkill.cpp::Activate --> Failed to start channeling")));
}

void UBaseSkill::Execute()
{
	if (GEngine) GEngine->AddOnScreenDebugMessage(4, 10.f, FColor::Blue, FString::Printf(TEXT("BaseSkill.cpp::Execute --> Executed a new skill!")));

	//Do the skilllogic
	SkillLogic();

	//Tell the system the skill is on cooldown
	m_SkillState = ESkillState::SS_IsOnCooldown;

	//Tell the timer to start the cooldown, if it completes make the skill castable again
	if (m_World)
		m_World->GetTimerManager().SetTimer(m_CoolDownTimerHandle, this, &UBaseSkill::SetCastable, m_CooldownDuration);

	//Clear the ChannelingTimer as it doesn't need to be active
	if (m_World)
		m_World->GetTimerManager().ClearTimer(m_ChannelingTimerHandle);
}

void UBaseSkill::Interupt()
{
	if (GEngine) GEngine->AddOnScreenDebugMessage(8, 10.f, FColor::Blue, FString::Printf(TEXT("BaseSkill.cpp::Interupt --> Interupted a new skill!")));

	//Tell the system the skill is on cooldown
	m_SkillState = ESkillState::SS_IsOnCooldown;

	//Tell the timer to start the cooldown, if it completes make the skill castable again
	if (m_World)
		m_World->GetTimerManager().SetTimer(m_CoolDownTimerHandle, this, &UBaseSkill::SetCastable, m_CooldownDuration * m_InteruptCooldownPercentage);

	//Clear the ChannelingTimer as it doesn't need to be active
	if (m_World)
		m_World->GetTimerManager().ClearTimer(m_ChannelingTimerHandle);
}

void UBaseSkill::SetCastable()
{
	if (GEngine) GEngine->AddOnScreenDebugMessage(16, 10.f, FColor::Blue, FString::Printf(TEXT("BaseSkill.cpp::SetCastable --> A skill is ready to be used again!")));

	//Tell the system the skill is castable
	m_SkillState = ESkillState::SS_IsCastable;

	//Clear the Cooldown as it doesn't need to be active
	if (m_World)
		m_World->GetTimerManager().ClearTimer(m_CoolDownTimerHandle);
}

void UBaseSkill::SkillLogic()
{
	if (GEngine) GEngine->AddOnScreenDebugMessage(5, 10.f, FColor::Blue, FString::Printf(TEXT("BaseSkill.cpp::SkillLogic --> BaseSkill has been used!")));
}

bool UBaseSkill::CanSkillBeUsed(float PlayerResourceAmmount)
{
	if(m_SkillState == ESkillState::SS_IsCastable && PlayerResourceAmmount >= m_ResourceCost)
		return true;

	if (GEngine) GEngine->AddOnScreenDebugMessage(32, 10.f, FColor::Red, FString::Printf(TEXT("BaseSkill.cpp::CanSkillBeUsed --> This skill cannot be used!")));
	return false;
}
