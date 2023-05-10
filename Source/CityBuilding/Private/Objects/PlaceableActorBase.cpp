// Fill out your copyright notice in the Description page of Project Settings.
#include "Objects/PlaceableActorBase.h"
#include "Objects/GridCellActor.h"
#include "Objects/RoadTileActor.h"
#include "Components/ClickableAComponent.h"
#include "Components/PlaceableAComponent.h"

#include "Components/SceneComponent.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
APlaceableActorBase::APlaceableActorBase()
{
	UniqueId = FMath::Rand();
	GLog->Log(FString::Printf(TEXT("APlaceableActorBase::%d::APlaceableActorBase()"), UniqueId));
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root Component"));
}

// Called when the game starts or when spawned
void APlaceableActorBase::BeginPlay()
{
	Super::BeginPlay();
	GLog->Log(FString::Printf(TEXT("APlaceableActorBase::%d::BeginPlay()"), UniqueId));
}

// Called every frame
void APlaceableActorBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APlaceableActorBase::OnActorOverlapBegin(AActor* OverlappedActor, AActor* OtherActor)
{
	GLog->Log(FString::Printf(TEXT("APlaceableActorBase::%d::OnActorOverlapBegin()"), UniqueId));
	OverlappedActorsCount++;
}

void APlaceableActorBase::OnActorOverlapEnd(AActor* OverlappedActor, AActor* OtherActor)
{
	GLog->Log(FString::Printf(TEXT("APlaceableActorBase::%d::OnActorOverlapEnd()"), UniqueId));
	OverlappedActorsCount--;
}

void APlaceableActorBase::AttachClickableComponent()
{
	GLog->Log(FString::Printf(TEXT("APlaceableActorBase::%d::AttachClickableComponent()"), UniqueId));
	ClickableComponent = NewObject<UClickableAComponent>(this, UClickableAComponent::StaticClass(), FName("Clickable Component"));
	ClickableComponent->RegisterComponent(); //Register will actually Initialize the Component
}

void APlaceableActorBase::DestroyClickableComponent()
{
	GLog->Log(FString::Printf(TEXT("APlaceableActorBase::%d::DestroyClickableComponent()"), UniqueId));
	if (ClickableComponent)
	{
		ClickableComponent->DestroyComponent();
	}
}

void APlaceableActorBase::AttachPlaceableComponent()
{
	GLog->Log(FString::Printf(TEXT("APlaceableActorBase::%d::AttachPlaceableComponent()"), UniqueId));
	PlaceableComponent = NewObject<UPlaceableAComponent>(this, UPlaceableAComponent::StaticClass(), FName("Placeable Component"));
	PlaceableComponent->RegisterComponent();
}

void APlaceableActorBase::DestroyPlaceableComponent()
{
	GLog->Log(FString::Printf(TEXT("APlaceableActorBase::%d::DestroyPlaceableComponent()"), UniqueId));
	if (PlaceableComponent)
	{
		PlaceableComponent->DestroyComponent();
	}
}

void APlaceableActorBase::OnActorPlaced()
{
	GLog->Log(FString::Printf(TEXT("APlaceableActorBase::%d::OnActorPlaced()"), UniqueId));

	BaseCell->OccupyingActor = this;
	BaseCell->BuildingType = BuildingType;
	switch (BuildingType)
	{
	case EBuildingType::E_Road:
	{
		if (BaseCell->North && BaseCell->North->OccupyingActor && BaseCell->North->BuildingType == BuildingType)
		{
			if (ARoadTileActor* Self = Cast<ARoadTileActor>(this))
			{
				Self->NorthPavement->SetVisibility(false);
				if (ARoadTileActor* North = Cast<ARoadTileActor>(BaseCell->North->OccupyingActor))
				{
					North->SouthPavement->SetVisibility(false);
				}
			}
		}
		if (BaseCell->South && BaseCell->South->OccupyingActor && BaseCell->South->BuildingType == BuildingType)
		{
			if (ARoadTileActor* Self = Cast<ARoadTileActor>(this))
			{
				Self->SouthPavement->SetVisibility(false);
				if (ARoadTileActor* South = Cast<ARoadTileActor>(BaseCell->South->OccupyingActor))
				{
					South->NorthPavement->SetVisibility(false);
				}
			}
		}
		if (BaseCell->East && BaseCell->East->OccupyingActor && BaseCell->East->BuildingType == BuildingType)
		{
			if (ARoadTileActor* Self = Cast<ARoadTileActor>(this))
			{
				Self->EastPavement->SetVisibility(false);
				if (ARoadTileActor* East = Cast<ARoadTileActor>(BaseCell->East->OccupyingActor))
				{
					East->WestPavement->SetVisibility(false);
				}
			}
		}
		if (BaseCell->West && BaseCell->West->OccupyingActor && BaseCell->West->BuildingType == BuildingType)
		{
			if (ARoadTileActor* Self = Cast<ARoadTileActor>(this))
			{
				Self->WestPavement->SetVisibility(false);
				if (ARoadTileActor* West = Cast<ARoadTileActor>(BaseCell->West->OccupyingActor))
				{
					West->EastPavement->SetVisibility(false);
				}
			}
		}
	}
	break;
	}
}