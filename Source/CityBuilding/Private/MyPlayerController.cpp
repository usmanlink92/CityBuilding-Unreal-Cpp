// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayerController.h"
#include "MyPawn.h"

#include "Objects/RoadTileActor.h"
#include "Objects/HouseTileActor.h"
#include "Objects/GridManagerActor.h"
#include "Objects/GridCellActor.h"

#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"

void AMyPlayerController::BeginPlay()
{
    Super::BeginPlay();
    GLog->Log(TEXT("AMyPlayerController::BeginPlay()"));
    bShowMouseCursor = true;
    bEnableClickEvents = true;
    bEnableMouseOverEvents = true;

    GridManagerActor = Cast<AGridManagerActor>(UGameplayStatics::GetActorOfClass(GetWorld(), AGridManagerActor::StaticClass()));
}

// Called every frame
void AMyPlayerController::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (!InPlacementMode && LeftMousePress)
    {
        SpawnCustomActor(BuildingType);
    }

    if (InPlacementMode)
    {
        UpdatePosition();
        DropActorAtLocation();
    }
}

void AMyPlayerController::BeginPlayingState()
{
    GLog->Log(TEXT("AMyPlayerController::BeginPlayingState()"));
    Super::BeginPlayingState();
    PlayerCharacter = Cast<AMyPawn>(GetPawn());
}

void AMyPlayerController::SetupInputComponent()
{
    Super::SetupInputComponent();
    GLog->Log(TEXT("AMyPlayerController::SetupInputComponent()"));

    // Bind movement inputs
    InputComponent->BindAction("MoveForward", IE_Pressed, this, &AMyPlayerController::MoveForward);
    InputComponent->BindAction("MoveForward", IE_Released, this, &AMyPlayerController::StopMoveForward);
    InputComponent->BindAction("MoveBackward", IE_Pressed, this, &AMyPlayerController::MoveBackward);
    InputComponent->BindAction("MoveBackward", IE_Released, this, &AMyPlayerController::StopMoveBackward);
    InputComponent->BindAction("MoveRight", IE_Pressed, this, &AMyPlayerController::MoveRight);
    InputComponent->BindAction("MoveRight", IE_Released, this, &AMyPlayerController::StopMoveRight);
    InputComponent->BindAction("MoveLeft", IE_Pressed, this, &AMyPlayerController::MoveLeft);
    InputComponent->BindAction("MoveLeft", IE_Released, this, &AMyPlayerController::StopMoveLeft);

    InputComponent->BindAction("ScrollUp", IE_Released, this, &AMyPlayerController::ScrollUp);
    InputComponent->BindAction("ScrollDown", IE_Released, this, &AMyPlayerController::ScrollDown);
    InputComponent->BindAction("MiddleMouse", IE_Pressed, this, &AMyPlayerController::MiddleMousePressed);
    InputComponent->BindAction("MiddleMouse", IE_Released, this, &AMyPlayerController::MiddleMouseReleased);

    InputComponent->BindAction("MouseLeftCLick", IE_Pressed, this, &AMyPlayerController::LeftMousePressed);
    InputComponent->BindAction("MouseLeftCLick", IE_Released, this, &AMyPlayerController::LeftMouseReleased);
    InputComponent->BindAction("MouseRightClick", IE_Released, this, &AMyPlayerController::CancelActorSpawn);

    InputComponent->BindAxis("MouseX", this, &AMyPlayerController::MouseX);
    InputComponent->BindAxis("MouseY", this, &AMyPlayerController::MouseY);
}

void AMyPlayerController::MouseX(float x)
{
    if (MiddleMousePress)
    {
        AddYawInput(x * 5.f);
    }
}

void AMyPlayerController::MouseY(float y)
{
    if (MiddleMousePress)
    {
        AddPitchInput(-y * 5.f);
    }
}

void AMyPlayerController::LeftMousePressed()
{
    GLog->Log(TEXT("AMyPlayerController::LeftMousePressed()"));
    LeftMousePress = true;
    if (BuildingType != EBuildingType::E_None)
    {
        SpawnCustomActor(BuildingType);
    }
}

void AMyPlayerController::LeftMouseReleased()
{
    GLog->Log(TEXT("AMyPlayerController::LeftMouseReleased()"));
    LeftMousePress = false;
    CancelActorSpawn();
}

void AMyPlayerController::MiddleMousePressed()
{
    GLog->Log(TEXT("AMyPlayerController::MiddleMousePressed()"));
    MiddleMousePress = true;
}

void AMyPlayerController::MiddleMouseReleased()
{
    GLog->Log(TEXT("AMyPlayerController::MiddleMouseReleased()"));
    MiddleMousePress = false;
}

void AMyPlayerController::MoveForward()
{
    GLog->Log(TEXT("AMyPlayerController::MoveForward()"));
    PlayerCharacter->IsMovingForward = true;
}

void AMyPlayerController::StopMoveForward()
{
    GLog->Log(TEXT("AMyPlayerController::StopMoveForward()"));
    PlayerCharacter->IsMovingForward = false;
}

void AMyPlayerController::MoveBackward()
{
    GLog->Log(TEXT("AMyPlayerController::MoveBackward()"));
    PlayerCharacter->IsMovingBackward = true;
}

void AMyPlayerController::StopMoveBackward()
{
    GLog->Log(TEXT("AMyPlayerController::StopMoveBackward()"));
    PlayerCharacter->IsMovingBackward = false;
}

void AMyPlayerController::MoveRight()
{
    GLog->Log(TEXT("AMyPlayerController::MoveRight()"));
    PlayerCharacter->IsMovingRight = true;
}

void AMyPlayerController::StopMoveRight()
{
    GLog->Log(TEXT("AMyPlayerController::StopMoveRight()"));
    PlayerCharacter->IsMovingRight = false;
}

void AMyPlayerController::MoveLeft()
{
    GLog->Log(TEXT("AMyPlayerController::MoveLeft()"));
    PlayerCharacter->IsMovingLeft = true;
}

void AMyPlayerController::StopMoveLeft()
{
    GLog->Log(TEXT("AMyPlayerController::StopMoveLeft()"));
    PlayerCharacter->IsMovingLeft = false;
}

void AMyPlayerController::ScrollUp()
{
    GLog->Log(TEXT("AMyPlayerController::ScrollUp()"));
    PlayerCharacter->SetSpringArm(-10.f);
}

void AMyPlayerController::ScrollDown()
{
    GLog->Log(TEXT("AMyPlayerController::ScrollDown()"));
    PlayerCharacter->SetSpringArm(+10.f);
}

void AMyPlayerController::SpawnCustomActor(EBuildingType Type)
{
    GLog->Log(TEXT("AMyPlayerController::SpawnCustomActor()"));
    if (!InPlacementMode && Type != EBuildingType::E_None)
    {
        InPlacementMode = true;
        FActorSpawnParameters SpawnParams;
        SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
        FVector _SpawnLocation = FVector::ZeroVector;
        _SpawnLocation.Z = -1000.f;
        TSubclassOf<APlaceableActorBase> PlaceableActorClassType;
        switch (Type)
        {
        case EBuildingType::E_Road:
            PlaceableActorClassType = ARoadTileActor::StaticClass();
        break;

        case EBuildingType::E_House:
            PlaceableActorClassType = AHouseTileActor::StaticClass();
            break;
        }
        PlaceableActor = GetWorld()->SpawnActor<APlaceableActorBase>(PlaceableActorClassType, _SpawnLocation, FRotator::ZeroRotator, SpawnParams);
        PlaceableActor->BuildingType = Type;
    }
}

void AMyPlayerController::DropActorAtLocation()
{
    GLog->Log(TEXT("AMyPlayerController::LeftClick()"));
    if (InPlacementMode && PlaceableActor->IsPlacementValid)
    {
        InPlacementMode = false;
        PlaceableActor->OnActorPlaced();
        PlaceableActor = nullptr;
    }
}

void AMyPlayerController::CancelActorSpawn()
{
    GLog->Log(TEXT("AMyPlayerController::RightClick()"));
    if (InPlacementMode)
    {
        InPlacementMode = false;
        PlaceableActor->Destroy();
        PlaceableActor = nullptr;
    }
}

void AMyPlayerController::UpdatePosition()
{
    FVector WorldLocation;
    FVector WorldDirection;
    FHitResult OutHit;
    if (DeprojectMousePositionToWorld(WorldLocation, WorldDirection) && (WorldLocation != LastWorldLocation || WorldDirection != LastWorldDirection))
    {
        LastWorldLocation = WorldLocation;
        LastWorldDirection = WorldDirection;
        if (GetWorld()->LineTraceSingleByChannel(OutHit, WorldLocation, (WorldLocation + (WorldDirection * 50000)), ECollisionChannel::ECC_GameTraceChannel1))
        {
            if (OutHit.bBlockingHit)
            {
                //GLog->Log(TEXT("AMyPlayerController::SetActorLocation()"));
                //BaseCellToBe : Will be NULL only if Grid Manager have nothing / have zero cells / No need to check null
                AGridCellActor* BaseCellToBe = Cast<AGridCellActor>(GridManagerActor->GetClosestPosition(OutHit.Location));
                if(BaseCellToBe->CellValidForType(PlaceableActor->BuildingType))
                {
                    //This 'if' cannot be combined with upper one, as upper one decides to return

                    //If same position, then no need to update Location
                    if (PlaceableActor->BaseCell != BaseCellToBe)
                    {
                        PlaceableActor->BaseCell = BaseCellToBe;
                        //Actor can move from one valid cell to another valid cell, so we Need to update Location irrespective of IsPlacementValid
                        PlaceableActor->SetActorLocation(PlaceableActor->BaseCell->GetActorLocation());
                        if (!PlaceableActor->IsPlacementValid)
                        {
                            PlaceableActor->IsPlacementValid = true;
                            PlaceableActor->SetMaterial(UConstants::GetMaterial(EColors::E_Grey));
                        }
                    }
                    return;
                }
                //Set invalid Location, with red color, below code will also run
                PlaceableActor->SetActorLocation(OutHit.Location);
            }
        }

        //When LineTrace is false
        if (PlaceableActor->IsPlacementValid)
        {
            PlaceableActor->IsPlacementValid = false;
            PlaceableActor->BaseCell = nullptr;
            PlaceableActor->SetMaterial(UConstants::GetMaterial(EColors::E_Red));
        }
    }
}