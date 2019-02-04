// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BaseCharacter.generated.h"

UCLASS()
class TOWERDEFENCE_API ABaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABaseCharacter();

public:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

#pragma region Movement
public:
	/**
	 * Base Function to move on the Forward vector
	 * @Param		AxisValue		scale of the movement
	 */
	virtual void MoveOnForward(float AxisValue);

	/**
 * Base Function to move on the Right vector
 * @Param		AxisValue		scale of the movement
 */
	virtual void MoveOnRight(float AxisValue);
#pragma endregion
};
