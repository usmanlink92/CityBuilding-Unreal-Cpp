#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "MyHUD.generated.h"

UCLASS()
class CITYBUILDING_API AMyHUD : public AHUD
{
    GENERATED_BODY()

    AMyHUD();
public:
    virtual void BeginPlay() override;

private:
    UPROPERTY(EditAnywhere, Category = "Widgets")
    TSubclassOf<class UMyWidget> MyWidgetClass;

    class UMyWidget* MyWidget;
};