// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerPawn.h"
#include "Components/InputComponent.h"
#include "Components/CapsuleComponent.h"
#include "Camera/CameraComponent.h"

APlayerPawn::APlayerPawn()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Create and attach a camera to the player
	m_Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	m_Camera->SetupAttachment(m_MainCollider);
}

void APlayerPawn::BeginPlay()
{
	Super::BeginPlay();
}

void APlayerPawn::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	//Camera
	RotateView();

}

void APlayerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MouseX", this, &APlayerPawn::YawCamera);
	PlayerInputComponent->BindAxis("MouseY", this, &APlayerPawn::PitchCamera);
}

#pragma region Camera
void APlayerPawn::YawCamera(float AxisValue)
{
	m_CameraInput.X = AxisValue;
}

void APlayerPawn::PitchCamera(float AxisValue)
{
	m_CameraInput.Y = AxisValue;
}

void APlayerPawn::RotateView()
{
	//Rotate the player pawn Yaw
	FRotator newRotation = GetActorRotation();
	newRotation.Yaw += m_CameraInput.X;
	SetActorRotation(newRotation);

	//Rotate the camera Pitch
	newRotation = m_Camera->GetComponentRotation();
	newRotation.Pitch = FMath::Clamp(newRotation.Pitch + m_CameraInput.Y, m_CameraPitchMin, m_CameraPitchMax);
	m_Camera->SetWorldRotation(newRotation);
}
#pragma endregion
