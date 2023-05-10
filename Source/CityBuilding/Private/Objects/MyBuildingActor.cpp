// Fill out your copyright notice in the Description page of Project Settings.
#include "Objects/MyBuildingActor.h"
#include "Components/ClickableAComponent.h"
#include "Components/PlaceableAComponent.h"

#include "Components/SceneComponent.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
AMyBuildingActor::AMyBuildingActor()
{
	UniqueId = FMath::Rand();
	GLog->Log(FString::Printf(TEXT("AMyBuildingActor::%d::AMyBuildingActor()"), UniqueId));
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    //static ConstructorHelpers::FObjectFinder<UStaticMesh> CubeMeshFinder(TEXT("/Game/Objects/MyCube")); // This can also be used for getting reference of UASSETS // Need to access Like: CubeMeshFinder.Object
	DefaultMaterial = Cast<UMaterialInterface>(StaticLoadObject(UMaterialInterface::StaticClass(), nullptr, TEXT("/Game/Materials/WhiteBase")));
	DefaultMesh = Cast<UStaticMesh>(StaticLoadObject(UStaticMesh::StaticClass(), nullptr, TEXT("/Game/Objects/MyCube")));
	
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root Component"));
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh"));
	Mesh->SetStaticMesh(DefaultMesh);
	Mesh->SetCollisionProfileName(TEXT("Buildings")); //Preset Created in Editor's Collision Settings
	Mesh->AttachTo(Root);
	Mesh->SetMaterial(0, DefaultMaterial); //A mesh can be composed of multiple Elements
	RootComponent = Root;

	OnActorBeginOverlap.AddDynamic(this, &AMyBuildingActor::OnActorOverlapBegin);
	OnActorEndOverlap.AddDynamic(this, &AMyBuildingActor::OnActorOverlapEnd);
}

// Called when the game starts or when spawned
void AMyBuildingActor::BeginPlay()
{
	Super::BeginPlay();
	GLog->Log(FString::Printf(TEXT("AMyBuildingActor::%d::BeginPlay()"), UniqueId));
}

// Called every frame
void AMyBuildingActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AMyBuildingActor::OnActorOverlapBegin(AActor* OverlappedActor, AActor* OtherActor)
{
	GLog->Log(FString::Printf(TEXT("AMyBuildingActor::%d::OnActorOverlapBegin()"), UniqueId));
	OverlappedActorsCount++;
}

void AMyBuildingActor::OnActorOverlapEnd(AActor* OverlappedActor, AActor* OtherActor)
{
	GLog->Log(FString::Printf(TEXT("AMyBuildingActor::%d::OnActorOverlapEnd()"), UniqueId));
	OverlappedActorsCount--;
}

void AMyBuildingActor::AttachClickableComponent()
{
	GLog->Log(FString::Printf(TEXT("AMyBuildingActor::%d::AttachClickableComponent()"), UniqueId));
	ClickableComponent = NewObject<UClickableAComponent>(this, UClickableAComponent::StaticClass(), FName("Clickable Component"));
	ClickableComponent->RegisterComponent(); //Register will actually Initialize the Component
}

void AMyBuildingActor::DestroyClickableComponent()
{
	GLog->Log(FString::Printf(TEXT("AMyBuildingActor::%d::DestroyClickableComponent()"), UniqueId));
	if (ClickableComponent)
	{
		ClickableComponent->DestroyComponent();
	}
}

void AMyBuildingActor::AttachPlaceableComponent()
{
	GLog->Log(FString::Printf(TEXT("AMyBuildingActor::%d::AttachPlaceableComponent()"), UniqueId));
	PlaceableComponent = NewObject<UPlaceableAComponent>(this, UPlaceableAComponent::StaticClass(), FName("Placeable Component"));
	PlaceableComponent->RegisterComponent();
}

void AMyBuildingActor::DestroyPlaceableComponent()
{
	GLog->Log(FString::Printf(TEXT("AMyBuildingActor::%d::DestroyPlaceableComponent()"), UniqueId));
	if (PlaceableComponent)
	{
		Mesh->SetMaterial(0, DefaultMaterial); //A mesh can be composed of multiple Elements
		PlaceableComponent->DestroyComponent();
	}
}