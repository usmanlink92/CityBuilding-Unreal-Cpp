// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
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
    virtual void Tick(float DeltaTime) override;
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
    void MiddleMousePressed();
    void MiddleMouseReleased();
    void MouseX(float x);
    void MouseY(float y);

    void SpawnCustomActor();

    bool MiddleMousePress = false;

    class AMyPawn* PlayerCharacter;

    class AMyBuildingActor* ExampleActor;
};
