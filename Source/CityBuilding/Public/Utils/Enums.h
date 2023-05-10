// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Enums.generated.h"


UENUM(BlueprintType)
enum class EBuildingType : uint8
{
	E_None,
	E_House,
	E_Road
};

UENUM(BlueprintType)
enum class EColors : uint8
{
	E_Default,
	E_White,
	E_Black,
	E_Yellow,
	E_Red,
	E_Green,
	E_Blue,
	E_Pink,
	E_Cyan,
	E_Grey
};

UCLASS()
class UEnums : public UObject
{
	GENERATED_BODY()
};

UCLASS()
class UConstants : public UObject
{
	GENERATED_BODY()
public:

	static UMaterialInterface* GetMaterial(const EColors& Color)
	{
		switch (Color)
		{
		case EColors::E_White:
			static UMaterialInterface* WhiteBase = Cast<UMaterialInterface>(StaticLoadObject(UMaterialInterface::StaticClass(), nullptr, TEXT("/Game/Materials/WhiteBase")));
			return WhiteBase;
			break;
			
		case EColors::E_Black:
			static UMaterialInterface* BlackBase = Cast<UMaterialInterface>(StaticLoadObject(UMaterialInterface::StaticClass(), nullptr, TEXT("/Game/Materials/BlackBase")));
			return BlackBase;
			break;
			
		case EColors::E_Yellow:
			static UMaterialInterface* YellowBase = Cast<UMaterialInterface>(StaticLoadObject(UMaterialInterface::StaticClass(), nullptr, TEXT("/Game/Materials/YellowBase")));
			return YellowBase;
			break;
			
		case EColors::E_Red:
			static UMaterialInterface* RedBase = Cast<UMaterialInterface>(StaticLoadObject(UMaterialInterface::StaticClass(), nullptr, TEXT("/Game/Materials/RedBase")));
			return RedBase;
			break;
			
		case EColors::E_Green:
			static UMaterialInterface* GreenBase = Cast<UMaterialInterface>(StaticLoadObject(UMaterialInterface::StaticClass(), nullptr, TEXT("/Game/Materials/GreenBase")));
			return GreenBase;
			break;
			
		case EColors::E_Blue:
			static UMaterialInterface* BlueBase = Cast<UMaterialInterface>(StaticLoadObject(UMaterialInterface::StaticClass(), nullptr, TEXT("/Game/Materials/BlueBase")));
			return BlueBase;
			break;
			
		case EColors::E_Cyan:
			static UMaterialInterface* CyanBase = Cast<UMaterialInterface>(StaticLoadObject(UMaterialInterface::StaticClass(), nullptr, TEXT("/Game/Materials/CyanBase")));
			return CyanBase;
			break;
			
		case EColors::E_Pink:
			static UMaterialInterface* PinkBase = Cast<UMaterialInterface>(StaticLoadObject(UMaterialInterface::StaticClass(), nullptr, TEXT("/Game/Materials/PinkBase")));
			return PinkBase;
			break;
			
		case EColors::E_Grey:
			static UMaterialInterface* GreyBase = Cast<UMaterialInterface>(StaticLoadObject(UMaterialInterface::StaticClass(), nullptr, TEXT("/Game/Materials/GreyBase")));
			return GreyBase;
			break;
		}
		return Cast<UMaterialInterface>(StaticLoadObject(UMaterialInterface::StaticClass(), nullptr, TEXT("/Game/Materials/WhiteBase")));
	}

	static UStaticMesh* GetMesh()
	{
		static UStaticMesh* Mesh = Cast<UStaticMesh>(StaticLoadObject(UStaticMesh::StaticClass(), nullptr, TEXT("/Game/Objects/MyCube")));
		return Mesh;
	}

	static const FLinearColor& GetRGBValue(const EColors& Color)
	{
		static FLinearColor RGB = FLinearColor(1, 1, 1);
		switch (Color)
		{
		case EColors::E_White:
			RGB = FLinearColor(1,1,1);
			break;

		case EColors::E_Black:
			RGB = FLinearColor(0,0,0);
			break;

		case EColors::E_Yellow:
			RGB = FLinearColor(1,1,0);
			break;

		case EColors::E_Red:
			RGB = FLinearColor(1,0,0);
			break;

		case EColors::E_Green:
			RGB = FLinearColor(0,1,0);
			break;

		case EColors::E_Blue:
			RGB = FLinearColor(0,0,1);
			break;

		case EColors::E_Cyan:
			RGB = FLinearColor(0,1,1);
			break;

		case EColors::E_Pink:
			RGB = FLinearColor(1,0,1);
			break;
		}
		return RGB;
	}

	static UMaterialInstanceDynamic* GetDynamicMaterial(const EColors& Color)
	{
		static UMaterialInterface* MyMaterial = Cast<UMaterialInterface>(StaticLoadObject(UMaterialInterface::StaticClass(), nullptr, TEXT("/Game/Materials/DynamicColor")));
		UMaterialInstanceDynamic* DynMaterial = UMaterialInstanceDynamic::Create(MyMaterial, nullptr);
		DynMaterial->SetVectorParameterValue(TEXT("Color"), GetRGBValue(Color));
		return DynMaterial;
	}
};
