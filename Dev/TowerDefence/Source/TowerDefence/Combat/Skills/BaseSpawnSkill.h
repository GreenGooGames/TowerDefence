// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Combat/Skills/BaseSkill.h"
#include "BaseSpawnSkill.generated.h"

class ABaseSkillActor;

UCLASS()
class TOWERDEFENCE_API UBaseSpawnSkill : public UBaseSkill
{
	GENERATED_BODY()

public:
	virtual void SkillLogic() override;

	TSubclassOf<ABaseSkillActor> m_SkillActorClass;

	TArray<ABaseSkillActor*> m_ActorsSpawned = {};
};
