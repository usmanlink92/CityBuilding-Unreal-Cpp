// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayerController.h"
#include "MyPawn.h"
#include "Objects/MyBuildingActor.h"

void AMyPlayerController::BeginPlay()
{
    Super::BeginPlay();
    GLog->Log(TEXT("AMyPlayerController::BeginPlay()"));
    bShowMouseCursor = true;
    bEnableClickEvents = true;
    bEnableMouseOverEvents = true;
}

// Called every frame
void AMyPlayerController::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
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

    InputComponent->BindAction("SpawnBuilding", IE_Released, this, &AMyPlayerController::SpawnCustomActor);

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
        PlayerCharacter->UpdateSpringArmPitch(-y * 5.f);
    }
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

void AMyPlayerController::SpawnCustomActor()
{
    GLog->Log(TEXT("AMyPlayerController::SpawnCustomActor()"));
    FActorSpawnParameters SpawnParams;
    SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
    ExampleActor = GetWorld()->SpawnActor<AMyBuildingActor>(AMyBuildingActor::StaticClass(), FVector::ZeroVector, FRotator::ZeroRotator, SpawnParams);
    ExampleActor->AttachClickableComponent();
}