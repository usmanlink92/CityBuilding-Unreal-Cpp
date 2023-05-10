// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Objects/PlaceableActorBase.h"
#include "HouseTileActor.generated.h"

UCLASS()
class CITYBUILDING_API AHouseTileActor : public APlaceableActorBase
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;
public:	
	// Sets default values for this actor's properties
	AHouseTileActor();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	class UStaticMeshComponent* TileBaseMesh;

	virtual void SetMaterial(UMaterialInterface*) override;

	const FVector GetRandomVector() const
	{
		return { RandomFloat() , RandomFloat() , RandomFloat() };
	}

	const float RandomFloat() const
	{
		return FMath::RandRange(0.5f, 0.9f);
	}
};
