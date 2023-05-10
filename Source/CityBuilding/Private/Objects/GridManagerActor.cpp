// Fill out your copyright notice in the Description page of Project Settings.
#include "Objects/GridManagerActor.h"
#include "Objects/GridCellActor.h"

#include "Kismet/KismetMathLibrary.h"

// Sets default values
AGridManagerActor::AGridManagerActor()
{
	GLog->Log(FString::Printf(TEXT("AGridManagerActor::AGridManagerActor()")));
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root Component"));	
	RootComponent = Root;
}

// Called when the game starts or when spawned
void AGridManagerActor::BeginPlay()
{
	Super::BeginPlay();
	GLog->Log(FString::Printf(TEXT("AGridManagerActor::BeginPlay()")));
	PopulateGrid();
	PopulateGridNeighbors();
}

void AGridManagerActor::PopulateGrid()
{
	GLog->Log(FString::Printf(TEXT("AGridManagerActor::PopulateGrid()")));
	const int Offset = (CellSize * GridLength * 0.5f) - (CellSize * 0.5f);
	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	FVector _SpawnLocation = FVector::ZeroVector;
	FRotator _SpawnRotator = FRotator::ZeroRotator;

	for (int i = 0; i < GridLength; i++)
	{
		_SpawnLocation.X = (i * CellSize) - Offset;
		for (int j = 0; j < GridLength; j++)
		{
			_SpawnLocation.Y = (j * CellSize) - Offset;
			AGridCellActor* NewCellObject = GetWorld()->SpawnActor<AGridCellActor>(AGridCellActor::StaticClass(), _SpawnLocation, _SpawnRotator, SpawnParams);
			NewCellObject->SetActorEnableCollision(false);
			Grid.Add(NewCellObject);
		}
	}
}

AActor* AGridManagerActor::GetClosestPosition(const FVector InPosition)
{
	//GLog->Log(FString::Printf(TEXT("AGridManagerActor::GetClosestPosition(%f, %f, %f)"), InPosition.X, InPosition.Y, InPosition.Z));
	AActor* CellRef = Grid.Num() > 0 ? Grid[0] : nullptr;
	FVector ClosestPosition = Grid.Num() > 0 ? Grid[0]->GetActorLocation() : FVector::ZeroVector;
	float Distance = Grid.Num() > 0 ? UKismetMathLibrary::Vector_Distance(InPosition, ClosestPosition) : FLT_MAX;
	for (AActor* Cell : Grid)
	{
		const FVector NewPosition = Cell->GetActorLocation();
		const float NewDistance = UKismetMathLibrary::Vector_Distance(NewPosition, InPosition);
		if (NewDistance <= Distance)
		{
			ClosestPosition = NewPosition;
			Distance = NewDistance;
			CellRef = Cell;
		}
	}
	return CellRef;
}


void AGridManagerActor::PopulateGridNeighbors()
{
	GLog->Log(FString::Printf(TEXT("AGridManagerActor::PopulateGridNeighbors()")));

	const int& GridCount = Grid.Num();
	for (int i = 0; i < GridCount; i++)
	{
		//North[i + GridLength]
		if ((i + GridLength) < GridCount)
		{
			Grid[i]->North = Grid[i + GridLength];
		}
		//South[i - GridLength]
		if ((i - GridLength) >= 0)
		{
			Grid[i]->South = Grid[i - GridLength];
		}
		//East[i + 1]
		if (((i + 1) % GridLength) != 0)
		{
			Grid[i]->East = Grid[i + 1];
		}
		//West[i - 1]
		if (i > 0 && ((i % GridLength) != 0))
		{
			Grid[i]->West = Grid[i - 1];
		}
	}
}