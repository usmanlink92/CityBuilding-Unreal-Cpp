// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "Utils/Enums.h"

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GridCellActor.generated.h"

UCLASS()
class CITYBUILDING_API AGridCellActor : public AActor
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
public:	
	// Sets default values for this actor's properties
	AGridCellActor();

	class AGridCellActor* North;
	class AGridCellActor* South;
	class AGridCellActor* East;
	class AGridCellActor* West;

	class APlaceableActorBase* OccupyingActor;
	EBuildingType BuildingType = EBuildingType::E_None;

	TMap<const EBuildingType, bool> LocationValidFor = { {EBuildingType::E_Road, true}, {EBuildingType::E_House, true} };

	void OnActorPlaced(class APlaceableActorBase*);
	//Check whether is this cell Valid for passed argument type of building?
	const bool CellValidForType(const EBuildingType& Type) const
	{
		if (OccupyingActor) return false;
		return LocationValidFor[Type];
	}

	void SetNeighborAvaiablility(AGridCellActor* AdjacentNeighbor, const EBuildingType& TypeToCheck)
	{
		if (AdjacentNeighbor)
		{
			AdjacentNeighbor->LocationValidFor[TypeToCheck] = AdjacentNeighbor->NeighborValidForType(TypeToCheck);
			if (TypeToCheck == EBuildingType::E_Road)
			{
				//North-East / South-East
				if (AdjacentNeighbor->East)
				{
					AdjacentNeighbor->LocationValidFor[TypeToCheck] = AdjacentNeighbor->NeighborValidForType(TypeToCheck);
				}
				//North-West / South-West
				if (AdjacentNeighbor->West)
				{
					AdjacentNeighbor->LocationValidFor[TypeToCheck] = AdjacentNeighbor->NeighborValidForType(TypeToCheck);
				}
			}
		}
	}

	const bool NeighborValidForType(const EBuildingType& Type) const
	{
		if (!OccupyingActor)
		{
			if (North && North->BuildingType == Type && North->OccupyingActor && East && East->BuildingType == Type && East->OccupyingActor && North->East)
			{
				if (Type == EBuildingType::E_Road && North->East->BuildingType == Type && North->East->OccupyingActor)
				{
					return false;
				}
				else if (Type == EBuildingType::E_House)
				{
					return false;
				}
			}
			if (North && North->BuildingType == Type && North->OccupyingActor && West && West->BuildingType == Type && West->OccupyingActor && North->West)
			{
				if (Type == EBuildingType::E_Road && North->West->BuildingType == Type && North->West->OccupyingActor)
				{
					return false;
				}
				else if (Type == EBuildingType::E_House)
				{
					return false;
				}
			}
			if (South && South->BuildingType == Type && South->OccupyingActor && East && East->BuildingType == Type && East->OccupyingActor && South->East)
			{
				if (Type == EBuildingType::E_Road && South->East->BuildingType == Type && South->East->OccupyingActor)
				{
					return false;
				}
				else if (Type == EBuildingType::E_House)
				{
					return false;
				}
			}
			if (South && South->BuildingType == Type && South->OccupyingActor && West && West->BuildingType == Type && West->OccupyingActor && South->West)
			{
				if (Type == EBuildingType::E_Road && South->West->BuildingType == Type && South->West->OccupyingActor)
				{
					return false;
				}
				else if (Type == EBuildingType::E_House)
				{
					return false;
				}
			}
			return true;
		}
		return false;
	}


};
