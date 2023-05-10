// Fill out your copyright notice in the Description page of Project Settings.
#include "MyPawn.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/SpringArmComponent.h"

// Sets default values
AMyPawn::AMyPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	GLog->Log(TEXT("AMyPawn::AMyPawn()"));
    SetDefaults();
    // Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
    bUseControllerRotationPitch = false;
    bUseControllerRotationRoll = false;
    bUseControllerRotationYaw = true;

    CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("RootCapsule"));
    CapsuleComponent->InitCapsuleSize(34.0f, 88.0f);
    CapsuleComponent->SetCollisionProfileName(UCollisionProfile::Pawn_ProfileName);

    CapsuleComponent->CanCharacterStepUpOn = ECB_No;
    CapsuleComponent->SetShouldUpdatePhysicsVolume(true);
    CapsuleComponent->SetCanEverAffectNavigation(false);
    CapsuleComponent->bDynamicObstacle = true;
    RootComponent = CapsuleComponent;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->TargetArmLength = SpringArmLength;
	const FRotator& CurrentRotation = GetActorRotation();
	SpringArm->SetWorldRotation(SpringArmWorldRotation);
	//SpringArm->bUsePawnControlRotation = true;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);
	Camera->bUsePawnControlRotation = true;
}

void AMyPawn::SetDefaults()
{
    GLog->Log(TEXT("AMyPawn::SetDefaults()"));
    InvertedMouse = true;
    SpringArmWorldRotation = { -60.f, 0.f, 0.f };
    SpringArmLength = MinSpringArmLength;
    UpdateMoveSpeed();
}

// Called when the game starts or when spawned
void AMyPawn::BeginPlay()
{
	Super::BeginPlay();
    GLog->Log(TEXT("AMyPawn::BeginPlay()"));

}

// Called every frame
void AMyPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    FVector NewLocation = GetActorLocation() + CurrentVelocity * DeltaTime;
    SetActorLocation(NewLocation);

    // Reset velocity for next tick
    CurrentVelocity = FVector::ZeroVector;

    // Update velocity based on movement state
    if (IsMovingForward)
    {
        FVector Direction = GetActorForwardVector();
        CurrentVelocity += Direction * MoveSpeed;
    }

    if (IsMovingBackward)
    {
        FVector Direction = GetActorForwardVector();
        CurrentVelocity -= Direction * MoveSpeed;
    }

    if (IsMovingRight)
    {
        FVector Direction = GetActorRightVector();
        CurrentVelocity += Direction * MoveSpeed;
    }

    if (IsMovingLeft)
    {
        FVector Direction = GetActorRightVector();
        CurrentVelocity -= Direction * MoveSpeed;
    }
}

void AMyPawn::UpdateSpringArmPitch(const float& Change)
{
    SpringArmWorldRotation.Pitch = FMath::Clamp<float>(SpringArmWorldRotation.Pitch + Change, 270.f, 350.f);
    SpringArm->SetRelativeRotation(SpringArmWorldRotation);
}

void AMyPawn::SetSpringArm(const float& Change)
{
    SpringArmLength += InvertedMouse ? Change*-1.f : Change;
    SpringArmLength = FMath::Clamp<float>(SpringArmLength, MinSpringArmLength, MaxSpringArmLength);
    SpringArm->TargetArmLength = SpringArmLength;
    UpdateMoveSpeed();
}

void AMyPawn::UpdateMoveSpeed()
{
    GLog->Log(TEXT("AMyPawn::UpdateMoveSpeed()"));
    MoveSpeed = (SpringArmLength / MinSpringArmLength) * 150.f;
}