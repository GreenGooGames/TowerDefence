// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CombatComponent.generated.h"

class UBaseSkill;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TOWERDEFENCE_API UCombatComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UCombatComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	
public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

#pragma region Combat Stats
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat Stats")
		int m_MaxHealth = 100.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat Stats")
		int m_MaxSpellResource = 100.0f;

private:
	int m_CurrentHealth = 0.0f;
	int m_CurrentSpellResource = 0.0f;
#pragma endregion

#pragma region Skills
public:
	void UseSkill(uint8 SkillId);

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skills")
	uint8 m_MaxActiveSkills = 5;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skills")
	TArray< TSubclassOf<UBaseSkill> > m_LearnableSkillsClasses = {};
	
private:
	TArray<UBaseSkill*> m_ActiveSkills = {};
#pragma endregion
};
