// Fill out your copyright notice in the Description page of Project Settings.

#include "BaseSpawnSkill.h"
#include "Engine/World.h"
#include "SkillComponents/BaseSkillActor.h"
#include "Components/BoxComponent.h"

void UBaseSpawnSkill::SkillLogic()
{
	//This is the default skill logic, there is no need to call this in an override method

	//Spawn an actor
	ABaseSkillActor* spawnedActor = GetWorld()->SpawnActor<ABaseSkillActor>(m_SkillActorClass, m_Instigator->GetActorLocation(), m_Instigator->GetActorRotation());
	m_ActorsSpawned.Add(spawnedActor);

	//Shoot the actor forward
	dynamic_cast<UBoxComponent*>(spawnedActor->GetRootComponent())->AddImpulse(spawnedActor->GetActorForwardVector()*100000000);
}