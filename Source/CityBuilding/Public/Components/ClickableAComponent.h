// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ClickableAComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UClickableAComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UClickableAComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	bool isClicked = false;

	TArray<class UMaterialInterface*> BaseColorMaterials;
	class UStaticMeshComponent* ControlledStaticMesh;

	UFUNCTION()
	void OnActorClicked(AActor* TouchedActor, FKey ButtonPressed);
	UFUNCTION()
	void OnActorHoverStart(AActor* TouchedActor);
	UFUNCTION()
	void OnActorHoverEnd(AActor* TouchedActor);
		
};
