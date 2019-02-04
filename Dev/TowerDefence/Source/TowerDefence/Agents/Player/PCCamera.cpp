// Fill out your copyright notice in the Description page of Project Settings.

#include "PCCamera.h"
#include "Engine/Components/ControllerSpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/PlayerController.h"
#include "Components/InputComponent.h"
#include "Agents/BaseCharacter.h"

APCCamera::APCCamera()
{
	m_SpringArm = CreateDefaultSubobject<UControllerSpringArmComponent>(TEXT("Spring Arm"));
	m_SpringArm->SetupAttachment(RootComponent);
	m_SpringArm->TargetArmLength = m_MaxZoomDistance;

	m_Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	m_Camera->SetupAttachment(m_SpringArm);
}

void APCCamera::Possess(APawn* InPawn)
{
	Super::Possess(InPawn);
	m_PossessedCharacter = dynamic_cast<ABaseCharacter*>(GetCharacter());
	m_SpringArm->m_FocusedActor = m_PossessedCharacter;
}

void APCCamera::UnPossess()
{
	Super::UnPossess();
	m_PossessedCharacter = nullptr;
	m_SpringArm->m_FocusedActor = m_PossessedCharacter;
}

#pragma region Camera
UCameraComponent* APCCamera::GetViewCamera()
{
	return m_Camera;
}

void APCCamera::ZoomCamera(float AxisValue)
{
	m_SpringArm->TargetArmLength += AxisValue * m_ZoomSpeed;
	m_SpringArm->TargetArmLength = FMath::Clamp(m_SpringArm->TargetArmLength, 0.0f, m_MaxZoomDistance);
}

void APCCamera::YawCamera(float AxisValue)
{
	if (m_PossessedCharacter == nullptr) 
		return;
	m_PossessedCharacter->AddControllerYawInput(AxisValue);
}

void APCCamera::PitchCamera(float AxisValue)
{
	FRotator newRotation = m_Camera->GetComponentRotation();
	newRotation.Pitch = FMath::Clamp(newRotation.Pitch + AxisValue, m_CameraPitchMin, m_CameraPitchMax);
	m_Camera->SetWorldRotation(newRotation);
}
#pragma endregion

#pragma  region Input
void APCCamera::SetupInputComponent()
{
	APlayerController::SetupInputComponent();

	InputComponent->BindAxis("MoveForward", this, &APCCamera::MoveOnForward);
	InputComponent->BindAxis("MoveBackward", this, &APCCamera::MoveOnForward);
	InputComponent->BindAxis("MoveRight", this, &APCCamera::MoveOnRight);
	InputComponent->BindAxis("MoveLeft", this, &APCCamera::MoveOnRight);
	InputComponent->BindAxis("MouseWheel", this, &APCCamera::ZoomCamera);
	InputComponent->BindAxis("MouseX", this, &APCCamera::YawCamera);
	InputComponent->BindAxis("MouseY", this, &APCCamera::PitchCamera);
}

void APCCamera::MoveOnForward(float AxisValue)
{
	if (m_PossessedCharacter)
		m_PossessedCharacter->MoveOnForward(AxisValue);
}

void APCCamera::MoveOnRight(float AxisValue)
{
	if (m_PossessedCharacter)
		m_PossessedCharacter->MoveOnRight(AxisValue);
}
#pragma endregion
