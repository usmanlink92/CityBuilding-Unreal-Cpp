// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Utils/Enums.h"
#include "GameFramework/PlayerController.h"
#include "MyPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class AMyPlayerController : public APlayerController
{
	GENERATED_BODY()

    virtual void BeginPlay() override;
    virtual void Tick(float) override;
    virtual void BeginPlayingState() override;
    virtual void SetupInputComponent() override;

    void MoveForward();
    void StopMoveForward();
    void MoveBackward();
    void StopMoveBackward();
    void MoveRight();
    void StopMoveRight();
    void MoveLeft();
    void StopMoveLeft();
    void ScrollUp();
    void ScrollDown();
    void LeftMousePressed();
    void LeftMouseReleased();
    void MiddleMousePressed();
    void MiddleMouseReleased();
    void MouseX(float);
    void MouseY(float);

    void DropActorAtLocation();
    void UpdatePosition();

    bool LeftMousePress = false;
    bool MiddleMousePress = false;
    bool InPlacementMode = false;

    EBuildingType BuildingType = EBuildingType::E_None;

    class AMyPawn* PlayerCharacter;
    class APlaceableActorBase* PlaceableActor;
    class AGridManagerActor* GridManagerActor;

    FVector LastWorldLocation = FVector::ZeroVector;
    FVector LastWorldDirection = FVector::ZeroVector;

public:
    void SetSpawnType(const EBuildingType& Type)
    {
        BuildingType = Type;
    }
    void SpawnCustomActor(EBuildingType);
    void CancelActorSpawn();
};
