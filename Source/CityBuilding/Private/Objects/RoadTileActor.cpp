// Fill out your copyright notice in the Description page of Project Settings.
#include "Objects/RoadTileActor.h"
#include "Utils/Enums.h"

#include "Components/SceneComponent.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
ARoadTileActor::ARoadTileActor() : Super()
{
	GLog->Log(FString::Printf(TEXT("ARoadTileActor::ARoadTileActor()")));
	// Set this actor to call Tick() every frame. You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	TileBaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TileBaseMesh"));
	TileBaseMesh->SetCollisionProfileName(TEXT("Buildings"));
	TileBaseMesh->SetStaticMesh(UConstants::GetMesh());
	TileBaseMesh->SetMaterial(0, UConstants::GetMaterial(EColors::E_Red));
	TileBaseMesh->SetWorldLocation({0.f, 0.f, -1.9f});
	TileBaseMesh->SetWorldScale3D({1.f, 1.f, 0.02f});
	TileBaseMesh->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepWorldTransform);

	NorthPavement = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("NorthPavement"));
	NorthPavement->SetCollisionProfileName(TEXT("Buildings"));
	NorthPavement->SetStaticMesh(UConstants::GetMesh());
	NorthPavement->SetMaterial(0, UConstants::GetMaterial(EColors::E_Yellow));
	NorthPavement->SetWorldLocation({45.f, 0.f, 100.f});
	NorthPavement->SetWorldScale3D({0.1f, 0.8f, 0.1f});
	NorthPavement->AttachToComponent(TileBaseMesh, FAttachmentTransformRules::KeepWorldTransform);

	SouthPavement = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SouthPavement"));
	SouthPavement->SetCollisionProfileName(TEXT("Buildings"));
	SouthPavement->SetStaticMesh(UConstants::GetMesh());
	SouthPavement->SetMaterial(0, UConstants::GetMaterial(EColors::E_Yellow));
	SouthPavement->SetWorldLocation({ -45.f, 0.f, 100.f });
	SouthPavement->SetWorldScale3D({ 0.1f, 0.8f, 0.1f });
	SouthPavement->AttachToComponent(TileBaseMesh, FAttachmentTransformRules::KeepWorldTransform);

	EastPavement = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("EastPavement"));
	EastPavement->SetCollisionProfileName(TEXT("Buildings"));
	EastPavement->SetStaticMesh(UConstants::GetMesh());
	EastPavement->SetMaterial(0, UConstants::GetMaterial(EColors::E_Yellow));
	EastPavement->SetWorldLocation({ 0.f, 45.f, 100.f });
	EastPavement->SetWorldScale3D({ 0.8f, 0.1f, 0.1f });
	EastPavement->AttachToComponent(TileBaseMesh, FAttachmentTransformRules::KeepWorldTransform);

	WestPavement = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WestPavement"));
	WestPavement->SetCollisionProfileName(TEXT("Buildings"));
	WestPavement->SetStaticMesh(UConstants::GetMesh());
	WestPavement->SetMaterial(0, UConstants::GetMaterial(EColors::E_Yellow));
	WestPavement->SetWorldLocation({ 0.f, -45.f, 100.f });
	WestPavement->SetWorldScale3D({ 0.8f, 0.1f, 0.1f });
	WestPavement->AttachToComponent(TileBaseMesh, FAttachmentTransformRules::KeepWorldTransform);

	NEPavement = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("NEPavement"));
	NEPavement->SetCollisionProfileName(TEXT("Buildings"));
	NEPavement->SetStaticMesh(UConstants::GetMesh());
	NEPavement->SetMaterial(0, UConstants::GetMaterial(EColors::E_Yellow));
	NEPavement->SetWorldLocation({45.f, 45.f, 100.f});
	NEPavement->SetWorldScale3D({0.1f, 0.1f, 0.1f});
	NEPavement->AttachToComponent(TileBaseMesh, FAttachmentTransformRules::KeepWorldTransform);

	SEPavement = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SEPavement"));
	SEPavement->SetCollisionProfileName(TEXT("Buildings"));
	SEPavement->SetStaticMesh(UConstants::GetMesh());
	SEPavement->SetMaterial(0, UConstants::GetMaterial(EColors::E_Yellow));
	SEPavement->SetWorldLocation({ -45.f, 45.f, 100.f });
	SEPavement->SetWorldScale3D({ 0.1f, 0.1f, 0.1f });
	SEPavement->AttachToComponent(TileBaseMesh, FAttachmentTransformRules::KeepWorldTransform);

	SWPavement = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SWPavement"));
	SWPavement->SetCollisionProfileName(TEXT("Buildings"));
	SWPavement->SetStaticMesh(UConstants::GetMesh());
	SWPavement->SetMaterial(0, UConstants::GetMaterial(EColors::E_Yellow));
	SWPavement->SetWorldLocation({ -45.f, -45.f, 100.f });
	SWPavement->SetWorldScale3D({ 0.1f, 0.1f, 0.1f });
	SWPavement->AttachToComponent(TileBaseMesh, FAttachmentTransformRules::KeepWorldTransform);

	NWPavement = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("NWPavement"));
	NWPavement->SetCollisionProfileName(TEXT("Buildings"));
	NWPavement->SetStaticMesh(UConstants::GetMesh());
	NWPavement->SetMaterial(0, UConstants::GetMaterial(EColors::E_Yellow));
	NWPavement->SetWorldLocation({ 45.f, -45.f, 100.f });
	NWPavement->SetWorldScale3D({ 0.1f, 0.1f, 0.1f });
	NWPavement->AttachToComponent(TileBaseMesh, FAttachmentTransformRules::KeepWorldTransform);
}

// Called when the game starts or when spawned
void ARoadTileActor::BeginPlay()
{
	Super::BeginPlay();
	GLog->Log(FString::Printf(TEXT("ARoadTileActor::BeginPlay()")));
}
void ARoadTileActor::SetMaterial(UMaterialInterface* Material)
{
	if (BaseMaterial != Material)
	{
		BaseMaterial = Material;
		TileBaseMesh->SetMaterial(0, BaseMaterial);
	}
}