// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyBuildingActor.generated.h"

UCLASS()
class CITYBUILDING_API AMyBuildingActor : public AActor
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
public:	
	// Sets default values for this actor's properties
	AMyBuildingActor();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	class USceneComponent* Root;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	class UStaticMeshComponent* Mesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	class UMaterialInterface* DefaultMaterial;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	class UClickableAComponent* ClickableComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	class UPlaceableAComponent* PlaceableComponent;

	void AttachClickableComponent();
	void DestroyClickableComponent();
	void AttachPlaceableComponent();
	void DestroyPlaceableComponent();
	int type = 0;
};
