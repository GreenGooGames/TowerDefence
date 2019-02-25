// Fill out your copyright notice in the Description page of Project Settings.

#include "CombatComponent.h"
#include "Skills/BaseSkill.h"
#include "Engine.h"
#include <string>

// Sets default values for this component's properties
UCombatComponent::UCombatComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	for (int i = 0; i < m_MaxActiveSkills; ++i)
	{
		m_ActiveSkills.Add(CreateDefaultSubobject<UBaseSkill>(TEXT("Skill" + i)));
	}
}


// Called when the game starts
void UCombatComponent::BeginPlay()
{
	Super::BeginPlay();
	
	// ...
	//m_ActiveSkills[0] = dynamic_cast<UBaseSkill*>(m_LearnableSkillsClasses[0]);
	
}


// Called every frame
void UCombatComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UCombatComponent::UseSkill(uint8 SkillId)
{
	if (m_ActiveSkills[SkillId]->CanSkillBeUsed(m_CurrentSpellResource))
		m_ActiveSkills[SkillId]->Activate(GetWorld(), dynamic_cast<APawn*>(GetOwner()));
	else
		if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("CombatComponent.cpp::UseSkill --> Cannot use the skill!")));
}

