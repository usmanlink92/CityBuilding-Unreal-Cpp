// Fill out your copyright notice in the Description page of Project Settings.
#include "Objects/GridCellActor.h"
#include "Objects/PlaceableActorBase.h"
#include "Objects/RoadTileActor.h"

// Sets default values
AGridCellActor::AGridCellActor()
{
	//GLog->Log(FString::Printf(TEXT("AGridCellActor::AGridCellActor()")));
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root Component"));
}

// Called when the game starts or when spawned
void AGridCellActor::BeginPlay()
{
	Super::BeginPlay();
	GLog->Log(FString::Printf(TEXT("AGridCellActor::BeginPlay()")));
}

// Called every frame
void AGridCellActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


void AGridCellActor::OnActorPlaced(APlaceableActorBase* Building)
{
	GLog->Log(TEXT("AGridCellActor::OnActorPlaced()"));

	OccupyingActor = Building;
	BuildingType = Building->BuildingType;

	SetNeighborAvaiablility(North, EBuildingType::E_Road);
	SetNeighborAvaiablility(North, EBuildingType::E_House);

	SetNeighborAvaiablility(South, EBuildingType::E_Road);
	SetNeighborAvaiablility(South, EBuildingType::E_House);

	SetNeighborAvaiablility(East, EBuildingType::E_Road);
	SetNeighborAvaiablility(East, EBuildingType::E_House);

	SetNeighborAvaiablility(West, EBuildingType::E_Road);
	SetNeighborAvaiablility(West, EBuildingType::E_House);

	//Set Road Pavement Visibility
	//Using 'this' because Accessing same variable from other object of same type
	switch (BuildingType)
	{
	case EBuildingType::E_Road:
	{
		if (North && North->OccupyingActor && North->BuildingType == BuildingType)
		{
			if (ARoadTileActor* Self = Cast<ARoadTileActor>(this->OccupyingActor))
			{
				if (ARoadTileActor* NorthX = Cast<ARoadTileActor>(North->OccupyingActor))
				{
					Self->NorthPavement->SetVisibility(false);
					NorthX->SouthPavement->SetVisibility(false);
				}
			}
		}
		if (South && South->OccupyingActor && South->BuildingType == BuildingType)
		{
			if (ARoadTileActor* Self = Cast<ARoadTileActor>(this->OccupyingActor))
			{
				if (ARoadTileActor* SouthX = Cast<ARoadTileActor>(South->OccupyingActor))
				{
					Self->SouthPavement->SetVisibility(false);
					SouthX->NorthPavement->SetVisibility(false);
				}
			}
		}
		if (East && East->OccupyingActor && East->BuildingType == BuildingType)
		{
			if (ARoadTileActor* Self = Cast<ARoadTileActor>(this->OccupyingActor))
			{
				if (ARoadTileActor* EastX = Cast<ARoadTileActor>(East->OccupyingActor))
				{
					Self->EastPavement->SetVisibility(false);
					EastX->WestPavement->SetVisibility(false);
				}
			}
		}
		if (West && West->OccupyingActor && West->BuildingType == BuildingType)
		{
			if (ARoadTileActor* Self = Cast<ARoadTileActor>(this->OccupyingActor))
			{
				if (ARoadTileActor* WestX = Cast<ARoadTileActor>(West->OccupyingActor))
				{
					Self->WestPavement->SetVisibility(false);
					WestX->EastPavement->SetVisibility(false);
				}
			}
		}
	}
	break;
	}
}