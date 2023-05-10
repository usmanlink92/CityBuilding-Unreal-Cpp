// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EmptyActor.generated.h"

UCLASS()
class CITYBUILDING_API AEmptyActor : public AActor
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
public:	
	// Sets default values for this actor's properties
	AEmptyActor();

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
};
