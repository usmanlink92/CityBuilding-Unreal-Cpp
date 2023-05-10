// Fill out your copyright notice in the Description page of Project Settings.
#include "Objects/GridCellActor.h"

#include "Components/SceneComponent.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
AGridCellActor::AGridCellActor()
{
	GLog->Log(FString::Printf(TEXT("AGridCellActor::AGridCellActor()")));
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	DefaultMaterial = Cast<UMaterialInterface>(StaticLoadObject(UMaterialInterface::StaticClass(), nullptr, TEXT("/Game/Materials/WhiteBase")));
	BlackMaterial = Cast<UMaterialInterface>(StaticLoadObject(UMaterialInterface::StaticClass(), nullptr, TEXT("/Game/Materials/BlackBase")));
	DefaultMesh = Cast<UStaticMesh>(StaticLoadObject(UStaticMesh::StaticClass(), nullptr, TEXT("/Game/Objects/MyCube")));

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root Component"));
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh"));
	Mesh->SetStaticMesh(DefaultMesh);
	Mesh->AttachTo(Root);
	Mesh->SetMaterial(0, DefaultMaterial); //A mesh can be composed of multiple Elements
	RootComponent = Root;
}

// Called when the game starts or when spawned
void AGridCellActor::BeginPlay()
{
	Super::BeginPlay();
	GLog->Log(FString::Printf(TEXT("AGridCellActor::BeginPlay()")));
}

// Called every frame
void AGridCellActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
