// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Agents/BaseCharacter.h"
#include "PlayerCharacter.generated.h"

class UCombatComponent;

UCLASS()
class TOWERDEFENCE_API APlayerCharacter : public ABaseCharacter
{
	GENERATED_BODY()

		APlayerCharacter();

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UCombatComponent* m_CombatComponent = nullptr;
};
