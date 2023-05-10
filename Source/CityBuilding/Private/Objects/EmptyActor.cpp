// Fill out your copyright notice in the Description page of Project Settings.
#include "Objects/EmptyActor.h"

#include "Components/SceneComponent.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
AEmptyActor::AEmptyActor()
{
	GLog->Log(FString::Printf(TEXT("AEmptyActor::AEmptyActor()")));
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	DefaultMaterial = Cast<UMaterialInterface>(StaticLoadObject(UMaterialInterface::StaticClass(), nullptr, TEXT("/Game/Materials/WhiteBase")));
	BlackMaterial = Cast<UMaterialInterface>(StaticLoadObject(UMaterialInterface::StaticClass(), nullptr, TEXT("/Game/Materials/BlackBase")));
	DefaultMesh = Cast<UStaticMesh>(StaticLoadObject(UStaticMesh::StaticClass(), nullptr, TEXT("/Game/Objects/MyCube")));

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root Component"));
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh"));
	Mesh->SetStaticMesh(DefaultMesh);
	Mesh->AttachTo(Root);
	Mesh->SetMaterial(0, DefaultMaterial); //A mesh can be composed of multiple Elements
	Mesh->SetWorldScale3D({0.15f, 0.15f, 0.15f});
	RootComponent = Root;

}

// Called when the game starts or when spawned
void AEmptyActor::BeginPlay()
{
	Super::BeginPlay();
	GLog->Log(FString::Printf(TEXT("AEmptyActor::BeginPlay()")));
}

// Called every frame
void AEmptyActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
