// Fill out your copyright notice in the Description page of Project Settings.
#include "Components/PlaceableAComponent.h"

#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"

// Sets default values for this component's properties
UPlaceableAComponent::UPlaceableAComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UPlaceableAComponent::BeginPlay()
{
	Super::BeginPlay();
	GetOwner()->OnClicked.AddDynamic(this, &UPlaceableAComponent::OnActorClicked);
	ControlledStaticMesh = Cast<UStaticMeshComponent>(GetOwner()->GetComponentByClass(UStaticMeshComponent::StaticClass()));

	
}


// Called every frame
void UPlaceableAComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UPlaceableAComponent::OnActorClicked(AActor* TouchedActor, FKey ButtonPressed)
{

}

