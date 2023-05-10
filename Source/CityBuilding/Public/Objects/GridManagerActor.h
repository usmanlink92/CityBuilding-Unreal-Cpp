// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GridManagerActor.generated.h"

UCLASS()
class CITYBUILDING_API AGridManagerActor : public AActor
{
	GENERATED_BODY()

private:
	int CellSize = 1000;
	int GridLength = 10;
	TArray<class AGridCellActor*> Grid;

	void PopulateGrid();

protected:
	virtual void BeginPlay() override;
public:	
	// Sets default values for this actor's properties
	AGridManagerActor();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	class USceneComponent* Root;

	AActor* GetClosestPosition(const FVector InPosition);
	void PopulateGridNeighbors();

};
