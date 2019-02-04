// Fill out your copyright notice in the Description page of Project Settings.

#include "CMThirdPerson.h"
#include "PCCamera.h"
#include "Camera/CameraComponent.h"

void ACMThirdPerson::UpdateViewTarget(FTViewTarget& OutVT, float DeltaTime)
{
	if ((PendingViewTarget.Target != NULL) && BlendParams.bLockOutgoing && OutVT.Equal(ViewTarget))
		return;

	bool bDoNotApplyModifiers = false;

	OutVT.POV.FOV = DefaultFOV;
	OutVT.POV.OrthoWidth = DefaultOrthoWidth;
	OutVT.POV.bConstrainAspectRatio = false;
	OutVT.POV.ProjectionMode = this->bIsOrthographic ? ECameraProjectionMode::Orthographic : ECameraProjectionMode::Perspective;
	OutVT.POV.PostProcessBlendWeight = 1.0f;

	APCCamera* playerController = dynamic_cast<APCCamera*>(GetOwningPlayerController());

	if (playerController)
	{
		UCameraComponent* viewCam = playerController->GetViewCamera();

		OutVT.POV.Location = viewCam->GetComponentLocation();
		OutVT.POV.Rotation = viewCam->GetComponentRotation();
		OutVT.POV.FOV = viewCam->FieldOfView;
		OutVT.POV.AspectRatio = viewCam->AspectRatio;
		OutVT.POV.bConstrainAspectRatio = viewCam->bConstrainAspectRatio;
		OutVT.POV.ProjectionMode = viewCam->ProjectionMode;
		OutVT.POV.OrthoWidth = viewCam->OrthoWidth;
		OutVT.POV.PostProcessBlendWeight = viewCam->PostProcessBlendWeight;

		if (playerController->GetViewCamera()->PostProcessBlendWeight > 0.0f)
		{
			OutVT.POV.PostProcessSettings = viewCam->PostProcessSettings;
		}

		if (!bDoNotApplyModifiers || this->bAlwaysApplyModifiers)
		{
			ApplyCameraModifiers(DeltaTime, OutVT.POV);
		}

		SetActorLocationAndRotation(OutVT.POV.Location, OutVT.POV.Rotation, false);
		UpdateCameraLensEffects(OutVT);
	}
	else
	{
		APlayerCameraManager::UpdateViewTarget(OutVT, DeltaTime);
	}
}
