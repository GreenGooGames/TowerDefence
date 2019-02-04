// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PCCamera.generated.h"

class UControllerSpringArmComponent;
class UCameraComponent;
class ABaseCharacter;

UCLASS()
class TOWERDEFENCE_API APCCamera : public APlayerController
{
	GENERATED_BODY()

		APCCamera();

protected:
	virtual void Possess(APawn* InPawn) override;
	virtual void UnPossess() override;

private:
	ABaseCharacter* m_PossessedCharacter = nullptr;

#pragma region Camera
public:
	/**
	 * Gets the Camera from the playerController
	 */
	UCameraComponent* GetViewCamera();

private:
	/**
	 * Changes the SpringArm length
	 * @Param		AxisValue		Direction used for zooming
	 */
	void ZoomCamera(float AxisValue);

	/**
	 * Rotate the character facing direction
	 * @Param		AxisValue		Direction for rotation
	 */
	void YawCamera(float AxisValue);

	/**
 * Rotate the camera facing direction
 * @Param		AxisValue		Direction for rotation
 */
	void PitchCamera(float AxisValue);


private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera", meta = (AllowPrivateAccess = "true"))
		UControllerSpringArmComponent* m_SpringArm = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera", meta = (AllowPrivateAccess = "true"))
		UCameraComponent* m_Camera = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera", meta = (AllowPrivateAccess = "true"))
		float m_MaxZoomDistance = 500.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera", meta = (AllowPrivateAccess = "true"))
		float m_ZoomSpeed = 10.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera", meta = (AllowPrivateAccess = "true"))
		float m_CameraPitchMin = -80.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera", meta = (AllowPrivateAccess = "true"))
		float m_CameraPitchMax = 80.0f;
#pragma endregion

#pragma region Input
protected:
	virtual void SetupInputComponent() override;

private:
	/**
 * Call MoveOnForward from the current possessed BaseCharacter
 * @Param		AxisValue		Scale of the movment
 */
	void MoveOnForward(float AxisValue);

	/**
	 * Call MoveOnRight from the current possessed BaseCharacter
	 * @Param		AxisValue		Scale of the movment
	 */
	void MoveOnRight(float AxisValue);
#pragma endregion
};
