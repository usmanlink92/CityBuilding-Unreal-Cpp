#include "MyHUD.h"

#include "UI/MyWidget.h"
#include "Blueprint/UserWidget.h"

AMyHUD::AMyHUD()
{
    GLog->Log(FString::Printf(TEXT("AMyHUD::AMyHUD()")));

    static ConstructorHelpers::FClassFinder<UUserWidget> HudWidgetObj(TEXT("/Game/Widgets/MyWidget_BP"));
    if (HudWidgetObj.Succeeded()) 
    {
        MyWidgetClass = HudWidgetObj.Class;
    }
    else 
    {
        MyWidgetClass = nullptr;
    }
}

void AMyHUD::BeginPlay()
{
    Super::BeginPlay();
    GLog->Log(FString::Printf(TEXT("AMyHUD::BeginPlay()")));

    MyWidget = CreateWidget<UMyWidget>(GetOwningPlayerController(), MyWidgetClass);
    if (MyWidget != nullptr)
    {
        MyWidget->AddToViewport();
    }
}