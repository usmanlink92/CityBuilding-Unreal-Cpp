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
	virtual void Tick(float DeltaTime) override;
public:	
	// Sets default values for this actor's properties
	AHouseTileActor();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	class UStaticMeshComponent* TileBaseMesh;

	virtual void SetMaterial(UMaterialInterface*) override;
};
