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

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	class USceneComponent* Root;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	class UStaticMeshComponent* Mesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	class UStaticMesh* DefaultMesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	class UMaterialInterface* DefaultMaterial;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	class UMaterialInterface* BlackMaterial;

	class AGridCellActor* North;
	class AGridCellActor* South;
	class AGridCellActor* East;
	class AGridCellActor* West;

	class AActor* OccupyingActor;

	EBuildingType BuildingType = EBuildingType::E_None;
};
