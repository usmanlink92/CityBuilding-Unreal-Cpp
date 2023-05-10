// Fill out your copyright notice in the Description page of Project Settings.
#include "Objects/HouseTileActor.h"
#include "Utils/Enums.h"

#include "Components/SceneComponent.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
AHouseTileActor::AHouseTileActor() : Super()
{
	GLog->Log(FString::Printf(TEXT("AHouseTileActor::AHouseTileActor()")));
	// Set this actor to call Tick() every frame. You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	TileBaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TileBaseMesh"));
	TileBaseMesh->SetCollisionProfileName(TEXT("Buildings"));
	TileBaseMesh->SetStaticMesh(UConstants::GetMesh());
	TileBaseMesh->SetMaterial(0, UConstants::GetMaterial(EColors::E_Red));
	TileBaseMesh->SetWorldLocation({0.f, 0.f, -1.9f});
	TileBaseMesh->SetWorldScale3D(GetRandomVector());
	TileBaseMesh->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepWorldTransform);
}

// Called when the game starts or when spawned
void AHouseTileActor::BeginPlay()
{
	Super::BeginPlay();
	GLog->Log(FString::Printf(TEXT("AHouseTileActor::BeginPlay()")));
}

void AHouseTileActor::SetMaterial(UMaterialInterface* Material)
{
	if (BaseMaterial != Material)
	{
		BaseMaterial = Material;
		TileBaseMesh->SetMaterial(0, BaseMaterial);
	}
}