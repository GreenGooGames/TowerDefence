// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Engine/EngineTypes.h"
#include "BaseSkill.generated.h"

UENUM(BlueprintType)
enum class ESkillState : uint8
{
	SS_IsBeingChanneled = 0,
	SS_IsOnCooldown = 1,
	SS_IsCastable = 2
};

UCLASS(Blueprintable)
class TOWERDEFENCE_API UBaseSkill : public UObject
{
	GENERATED_BODY()

public:
	/**Activates the skill*/
	virtual void Activate(UWorld* World, APawn* Instigator);
	/**Defines the logic to be executed when the skill is used (internal cool/cast time handling)*/
	UFUNCTION()
	virtual void Execute();
	/**Defines the logic that has to happend when a skill should be cancelled*/
	virtual void Interupt();
	/**Defines logic that happends when the skill becomes availble for re-castings*/
	UFUNCTION()
	virtual void SetCastable();

	/**Defines the logic of the skill*/
	virtual void SkillLogic();

	/**Defines the condition logic to check if a skill can be used*/
	virtual bool CanSkillBeUsed(float PlayerResourceAmmount);

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skill Properties")
		float m_CooldownDuration = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skill Properties")
		float m_ChannelingDuration = 0.2f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skill Properties")
		float m_InteruptCooldownPercentage = 0.1f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skill Properties")
		float m_ResourceCost = 0.0f;

protected:
	APawn* m_Instigator = nullptr;

private:
	FTimerHandle m_CoolDownTimerHandle;
	FTimerHandle m_ChannelingTimerHandle;
	ESkillState m_SkillState = ESkillState::SS_IsCastable;
	UWorld* m_World = nullptr;
};
