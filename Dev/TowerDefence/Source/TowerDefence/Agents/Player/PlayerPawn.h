// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Agents/BasePawn.h"
#include "PlayerPawn.generated.h"

UCLASS()
class TOWERDEFENCE_API APlayerPawn : public ABasePawn
{
	GENERATED_BODY()

public:
	APlayerPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaSeconds) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

#pragma region Camera
private:
	void YawCamera(float AxisValue);
	void PitchCamera(float AxisValue);
	void RotateView();

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
		UCameraComponent* m_Camera = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
		float m_ZoomSpeed = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
		float m_CameraPitchMin = -80.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
		float m_CameraPitchMax = 80.0f;

private:
	FVector2D m_CameraInput = { 0.0f, 0.0f };
#pragma endregion
};
