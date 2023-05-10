// Fill out your copyright notice in the Description page of Project Settings.
#include "Objects/PlaceableActorBase.h"
#include "Objects/GridCellActor.h"

// Sets default values
APlaceableActorBase::APlaceableActorBase()
{
	GLog->Log(FString::Printf(TEXT("APlaceableActorBase::APlaceableActorBase()")));
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root Component"));
}

// Called when the game starts or when spawned
void APlaceableActorBase::BeginPlay()
{
	Super::BeginPlay();
	GLog->Log(FString::Printf(TEXT("APlaceableActorBase::BeginPlay()")));
}

void APlaceableActorBase::OnActorPlaced()
{
	GLog->Log(FString::Printf(TEXT("APlaceableActorBase::OnActorPlaced()")));
	//Placement Confirmed, update Neighbor Cells
	BaseCell->OnActorPlaced(this);
}