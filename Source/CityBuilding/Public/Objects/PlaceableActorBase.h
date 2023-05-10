// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Utils/Enums.h"
#include "PlaceableActorBase.generated.h"

UCLASS()
class CITYBUILDING_API APlaceableActorBase : public AActor
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

public:	
	// Sets default values for this actor's properties
	APlaceableActorBase();

	void OnActorPlaced();
	
	class AGridCellActor* BaseCell;

	//Every Child Class will set/use this variable
	UMaterialInterface* BaseMaterial;
	virtual void SetMaterial(UMaterialInterface* Material) { BaseMaterial = Material; };

	bool IsPlacementValid = false;

	//This is set on SpawnActor
	EBuildingType BuildingType = EBuildingType::E_None;
};
