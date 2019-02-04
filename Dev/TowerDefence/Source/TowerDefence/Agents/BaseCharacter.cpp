// Fill out your copyright notice in the Description page of Project Settings.

#include "BaseCharacter.h"

// Sets default values
ABaseCharacter::ABaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

#pragma region Movement
void ABaseCharacter::MoveOnForward(float AxisValue)
{
	AddMovementInput(GetActorForwardVector(), AxisValue, false);
}

void ABaseCharacter::MoveOnRight(float AxisValue)
{
	AddMovementInput(GetActorRightVector(), AxisValue, false);
}
#pragma endregion