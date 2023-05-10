// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PlaceableAComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UPlaceableAComponent : public UActorComponent
{
	GENERATED_BODY()
	
	int32 UniqueId = 0;
	void Initialize();

public:	
	// Sets default values for this component's properties
	UPlaceableAComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	class UStaticMeshComponent* ControlledStaticMesh;

	UFUNCTION()
	void OnActorClicked(AActor* TouchedActor, FKey ButtonPressed);
	UFUNCTION()
	void OnActorOverlapBegin(AActor* OverlappedActor, AActor* OtherActor);
	UFUNCTION()
	void OnActorOverlapEnd(AActor* OverlappedActor, AActor* OtherActor);
	

public:
	bool IsPlacementValid = false;
	class AMyBuildingActor* BuildingParent = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	class UMaterialInterface* ValidStateMaterial;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	class UMaterialInterface* InValidStateMaterial;

	void UpdateOverlappingState();
};
