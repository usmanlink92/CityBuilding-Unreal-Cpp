// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
//#include "GameFramework/UserDefinedEnum.h"
#include "Enums.generated.h"


UENUM(BlueprintType)
enum class EBuildingType : uint8
{
	E_None,
	E_House,
	E_Road
};

UCLASS()
class UEnums : public UObject
{
	GENERATED_BODY()
};
