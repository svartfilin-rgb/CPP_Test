// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

/** Main log category used across the project */
DECLARE_LOG_CATEGORY_EXTERN(LogCPP_Test, Log, All);



UENUM(BlueprintType)
enum class EDamageType : uint8
{
	Physical,
	Fire,
	Ice,
	Explosion,

};

