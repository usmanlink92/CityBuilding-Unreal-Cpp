// Fill out your copyright notice in the Description page of Project Settings.
#include "Objects/GridCellActor.h"

// Sets default values
AGridCellActor::AGridCellActor()
{
	GLog->Log(FString::Printf(TEXT("AGridCellActor::AGridCellActor()")));
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
