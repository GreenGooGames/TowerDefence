// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerCharacter.h"
#include "Combat/CombatComponent.h"

APlayerCharacter::APlayerCharacter()
{
	m_CombatComponent = CreateDefaultSubobject<UCombatComponent>(TEXT("CombatComponent"));
}