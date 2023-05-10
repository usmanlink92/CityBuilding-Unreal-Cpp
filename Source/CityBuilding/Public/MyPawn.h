// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "MyPawn.generated.h"

UCLASS()
class AMyPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AMyPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:	

	/** The CapsuleComponent being used for movement collision (by CharacterMovement). Always treated as being vertically aligned in simple collision check functions. */
	UPROPERTY(Category = Character, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		class UCapsuleComponent* CapsuleComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		class USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		class UCameraComponent* Camera;

	bool IsMovingForward = false;
	bool IsMovingBackward = false;
	bool IsMovingRight = false;
	bool IsMovingLeft = false;

	void SetSpringArm(const float& Change);
	void UpdateSpringArmPitch(const float& Change);


private:
	void SetDefaults();
	void UpdateMoveSpeed();
	FVector CurrentVelocity;
	FRotator SpringArmWorldRotation = FRotator::ZeroRotator;
	float MoveSpeed = 100.f;
	bool InvertedMouse = false;
	float SpringArmLength = 0.f;
	//float SpringArmPitch = 0.f;
	float MinSpringArmLength = 400.f;
	float MaxSpringArmLength = 4000.f;
};
