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

	//Check whether is this cell Valid for passed argument type of building?
	const bool IsValidForType(const EBuildingType& Type) const
	{
		GLog->Log(FString::Printf(TEXT("AGridCellActor::IsValidCell() | Actor:%s | Cell:%s"), *UEnum::GetValueAsString(Type), *UEnum::GetValueAsString(BuildingType)));
		if(!OccupyingActor)
		{
			if (Type == EBuildingType::E_Road)
			{
				if (North && North->OccupyingActor && East && East->OccupyingActor && North->East && North->East->OccupyingActor)
				{
					return false;
				}
				if (North && North->OccupyingActor && West && West->OccupyingActor && North->West && North->West->OccupyingActor)
				{
					return false;
				}
				if (South && South->OccupyingActor && East && East->OccupyingActor && South->East && South->East->OccupyingActor)
				{
					return false;
				}
				if (South && South->OccupyingActor && West && West->OccupyingActor && South->West && South->West->OccupyingActor)
				{
					return false;
				}
				return true;
			}
		}
		return false;
	}
};
