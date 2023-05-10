#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MyWidget.generated.h"

UCLASS()
class CITYBUILDING_API UMyWidget : public UUserWidget
{
    GENERATED_BODY()

public:
    virtual void NativeConstruct() override;

private:
    UPROPERTY(meta = (BindWidget))
    class UButton* RoadBtn;
    UPROPERTY(meta = (BindWidget))
    class UButton* HouseBtn;

    UPROPERTY(meta = (BindWidget))
    class UTextBlock* MyTextView;

    UPROPERTY(meta = (BindWidget))
    class UEditableTextBox* MyEditableTextField;

    UPROPERTY(meta = (BindWidget))
    class UImage* MyImage;

    UFUNCTION()
    void OnRoadBtnClicked();
    UFUNCTION()
    void OnHouseBtnClicked();

    bool RoadSelected;
    bool HouseSelected;

    class AMyPlayerController* PlayerController;
};
