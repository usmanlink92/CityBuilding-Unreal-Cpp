// Fill out your copyright notice in the Description page of Project Settings.
#include "Components/PlaceableAComponent.h"
#include "Objects/MyBuildingActor.h"
#include "Objects/PlaceableActorBase.h"

#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"

// Sets default values for this component's properties
UPlaceableAComponent::UPlaceableAComponent()
{
	UniqueId = FMath::Rand();
	GLog->Log(FString::Printf(TEXT("UPlaceableAComponent::%d::UPlaceableAComponent()"), UniqueId));
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	ValidStateMaterial = Cast<UMaterialInterface>(StaticLoadObject(UMaterialInterface::StaticClass(), nullptr, TEXT("/Game/Materials/CyanBase")));
	InValidStateMaterial = Cast<UMaterialInterface>(StaticLoadObject(UMaterialInterface::StaticClass(), nullptr, TEXT("/Game/Materials/RedBase")));

	Initialize();
	
}

// Called when the game starts
void UPlaceableAComponent::BeginPlay()
{
	Super::BeginPlay();
	GLog->Log(FString::Printf(TEXT("UPlaceableAComponent::%d::BeginPlay()"), UniqueId));
	if (!BuildingParent) //Sometimes GetOwner() is not valid in Constructor. So initialization in BeginPlay.
	{
		Initialize();
	}
	UpdateOverlappingState();
}

// Called every frame
void UPlaceableAComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

// Called when the game starts
void UPlaceableAComponent::Initialize()
{
	GLog->Log(FString::Printf(TEXT("UPlaceableAComponent::%d::Initialize()"), UniqueId));

	if (GetOwner())
	{
		BuildingParent = Cast<APlaceableActorBase>(GetOwner());
		BuildingParent->OnClicked.AddDynamic(this, &UPlaceableAComponent::OnActorClicked);
		BuildingParent->OnActorBeginOverlap.AddDynamic(this, &UPlaceableAComponent::OnActorOverlapBegin);
		BuildingParent->OnActorEndOverlap.AddDynamic(this, &UPlaceableAComponent::OnActorOverlapEnd);
		ControlledStaticMesh = Cast<UStaticMeshComponent>(BuildingParent->GetComponentByClass(UStaticMeshComponent::StaticClass()));
		ControlledStaticMesh->SetMaterial(0, InValidStateMaterial);
	}
}

void UPlaceableAComponent::UpdateOverlappingState()
{
	GLog->Log(TEXT("UPlaceableAComponent::UpdateState()"));
	if (BuildingParent)
	{
		IsPlacementValid = (BuildingParent->OverlappedActorsCount == 0);
		ControlledStaticMesh->SetMaterial(0, IsPlacementValid ? ValidStateMaterial : InValidStateMaterial);
	}
}

void UPlaceableAComponent::OnActorClicked(AActor* TouchedActor, FKey ButtonPressed)
{
	GLog->Log(FString::Printf(TEXT("UPlaceableAComponent::%d::OnActorClicked()"), UniqueId));

}

void UPlaceableAComponent::OnActorOverlapBegin(AActor* OverlappedActor, AActor* OtherActor)
{
	GLog->Log(FString::Printf(TEXT("UPlaceableAComponent::%d::OnActorOverlapBegin()"), UniqueId));
	UpdateOverlappingState();
}

void UPlaceableAComponent::OnActorOverlapEnd(AActor* OverlappedActor, AActor* OtherActor)
{
	GLog->Log(FString::Printf(TEXT("UPlaceableAComponent::%d::OnActorOverlapEnd()"), UniqueId));
	UpdateOverlappingState();
}