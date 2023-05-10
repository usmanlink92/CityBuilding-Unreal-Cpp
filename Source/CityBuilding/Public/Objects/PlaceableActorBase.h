// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Utils/Enums.h"
#include "PlaceableActorBase.generated.h"

UCLASS()
class CITYBUILDING_API APlaceableActorBase : public AActor
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

public:	
	// Sets default values for this actor's properties
	APlaceableActorBase();

	void AttachClickableComponent();
	void DestroyClickableComponent();
	void AttachPlaceableComponent();
	void DestroyPlaceableComponent();

	void OnActorPlaced();
	

	UMaterialInterface* BaseMaterial;
	virtual void SetMaterial(UMaterialInterface* Material) { BaseMaterial = Material; };
	//virtual void RoadAtNorth();

	uint8 OverlappedActorsCount = 0;

	bool IsPlacementValid = false;
	class UClickableAComponent* ClickableComponent;
	class UPlaceableAComponent* PlaceableComponent;
	class AGridCellActor* BaseCell;
	EBuildingType BuildingType = EBuildingType::E_None;

private:
	int32 UniqueId = 0;
	UFUNCTION()
	void OnActorOverlapBegin(AActor* OverlappedActor, AActor* OtherActor);
	UFUNCTION()
	void OnActorOverlapEnd(AActor* OverlappedActor, AActor* OtherActor);
};
