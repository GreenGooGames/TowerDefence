// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SpringArmComponent.h"
#include "ControllerSpringArmComponent.generated.h"

class ACharacter;

UCLASS()
class TOWERDEFENCE_API UControllerSpringArmComponent : public USpringArmComponent
{
	GENERATED_BODY()

protected:
	virtual void UpdateDesiredArmLocation(bool bDoTrace, bool bDoLocationLag, bool bDoRotationLag, float DeltaTime) override;

public:
	ACharacter* m_FocusedCharacter = nullptr;
};
