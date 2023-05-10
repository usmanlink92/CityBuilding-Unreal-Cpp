// Fill out your copyright notice in the Description page of Project Settings.
#include "Components/ClickableAComponent.h"

#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"

// Sets default values for this component's properties
UClickableAComponent::UClickableAComponent()
{
	GLog->Log(TEXT("UClickableAComponent::UClickableAComponent()"));
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	BaseColorMaterials.Add(Cast<UMaterialInterface>(StaticLoadObject(UMaterialInterface::StaticClass(), nullptr, TEXT("/Game/Materials/RedBase"))));
	BaseColorMaterials.Add(Cast<UMaterialInterface>(StaticLoadObject(UMaterialInterface::StaticClass(), nullptr, TEXT("/Game/Materials/GreenBase"))));
	BaseColorMaterials.Add(Cast<UMaterialInterface>(StaticLoadObject(UMaterialInterface::StaticClass(), nullptr, TEXT("/Game/Materials/BlueBase"))));
	BaseColorMaterials.Add(Cast<UMaterialInterface>(StaticLoadObject(UMaterialInterface::StaticClass(), nullptr, TEXT("/Game/Materials/PinkBase"))));

}


// Called when the game starts
void UClickableAComponent::BeginPlay()
{
	Super::BeginPlay();
	GLog->Log(TEXT("UClickableAComponent::BeginPlay()"));

	GetOwner()->OnClicked.AddDynamic(this, &UClickableAComponent::OnActorClicked);
	GetOwner()->OnBeginCursorOver.AddDynamic(this, &UClickableAComponent::OnActorHoverStart);
	GetOwner()->OnEndCursorOver.AddDynamic(this, &UClickableAComponent::OnActorHoverEnd);
	ControlledStaticMesh = Cast<UStaticMeshComponent>(GetOwner()->GetComponentByClass(UStaticMeshComponent::StaticClass()));

}


// Called every frame
void UClickableAComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}


void UClickableAComponent::OnActorClicked(AActor* TouchedActor, FKey ButtonPressed)
{
	GLog->Log(TEXT("UClickableAComponent::OnActorClicked()"));
	isClicked = !isClicked;
	ControlledStaticMesh->SetMaterial(0, BaseColorMaterials[FMath::RandRange(0,3)]);
}
void UClickableAComponent::OnActorHoverStart(AActor* TouchedActor)
{
	GLog->Log(TEXT("UClickableAComponent::OnActorHoverStart()"));
	ControlledStaticMesh->SetRenderCustomDepth(true);
}
void UClickableAComponent::OnActorHoverEnd(AActor* TouchedActor)
{
	GLog->Log(TEXT("UClickableAComponent::OnActorHoverEnd()"));
	ControlledStaticMesh->SetRenderCustomDepth(false);

}
