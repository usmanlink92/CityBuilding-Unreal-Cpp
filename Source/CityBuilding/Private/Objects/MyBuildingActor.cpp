// Fill out your copyright notice in the Description page of Project Settings.
#include "Objects/MyBuildingActor.h"
#include "Components/ClickableAComponent.h"
#include "Components/PlaceableAComponent.h"

#include "Components/SceneComponent.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
AMyBuildingActor::AMyBuildingActor()
{
	GLog->Log(FString::Printf(TEXT("AMyBuildingActor::AMyBuildingActor() %d"), type));
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    static ConstructorHelpers::FObjectFinder<UStaticMesh> CubeMeshFinder(TEXT("/Game/Objects/MyCube"));
	DefaultMaterial = Cast<UMaterialInterface>(StaticLoadObject(UMaterialInterface::StaticClass(), nullptr, TEXT("/Game/Materials/WhiteBase")));
	
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root Component"));
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh"));
	Mesh->SetStaticMesh(CubeMeshFinder.Object);
	Mesh->SetCollisionProfileName(TEXT("Buildings"));
	Mesh->AttachTo(Root);
	Mesh->SetMaterial(0, DefaultMaterial);
	RootComponent = Root;

}

void AMyBuildingActor::AttachClickableComponent()
{
	GLog->Log(TEXT("AMyBuildingActor::AttachClickableComponent()"));
	ClickableComponent = NewObject<UClickableAComponent>(this, UClickableAComponent::StaticClass(), FName("Clickable Component"));
	ClickableComponent->RegisterComponent();
}

void AMyBuildingActor::DestroyClickableComponent()
{
	GLog->Log(TEXT("AMyBuildingActor::DestroyClickableComponent()"));
	if (ClickableComponent)
	{
		ClickableComponent->DestroyComponent();
	}
}

void AMyBuildingActor::AttachPlaceableComponent()
{
	GLog->Log(TEXT("AMyBuildingActor::AttachPlaceableComponent()"));
	PlaceableComponent = NewObject<UPlaceableAComponent>(this, UPlaceableAComponent::StaticClass(), FName("Placeable Component"));
	PlaceableComponent->RegisterComponent();
}

void AMyBuildingActor::DestroyPlaceableComponent()
{
	GLog->Log(TEXT("AMyBuildingActor::DestroyPlaceableComponent()"));
	if (PlaceableComponent)
	{
		PlaceableComponent->DestroyComponent();
	}
}

// Called when the game starts or when spawned
void AMyBuildingActor::BeginPlay()
{
	Super::BeginPlay();
	GLog->Log(FString::Printf(TEXT("AMyBuildingActor::BeginPlay() %d"), type));
}

// Called every frame
void AMyBuildingActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

