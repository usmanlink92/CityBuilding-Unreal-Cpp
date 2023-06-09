// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameModeBase.h"
#include "MyPlayerController.h"
#include "MyPawn.h"
#include "MyHUD.h"

AMyGameModeBase::AMyGameModeBase()
{
	GLog->Log(TEXT("AMyGameModeBase::AMyGameModeBase()"));
	DefaultPawnClass = AMyPawn::StaticClass();
	PlayerControllerClass = AMyPlayerController::StaticClass();
	HUDClass = AMyHUD::StaticClass();
}