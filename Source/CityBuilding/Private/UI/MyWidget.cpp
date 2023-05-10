#include "UI/MyWidget.h"
#include "MyPlayerController.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/EditableTextBox.h"
#include "Components/Image.h"

void UMyWidget::NativeConstruct()
{
    Super::NativeConstruct();
    GLog->Log(FString::Printf(TEXT("UMyWidget::NativeConstruct()")));

    PlayerController = Cast<AMyPlayerController>(GetOwningPlayer());
    MyTextView->SetVisibility(ESlateVisibility::Hidden);
    MyEditableTextField->SetVisibility(ESlateVisibility::Hidden);
    MyImage->SetVisibility(ESlateVisibility::Hidden);
    // Bind the button click event
    if (RoadBtn != nullptr && HouseBtn != nullptr)
    {
        RoadBtn->OnClicked.AddDynamic(this, &UMyWidget::OnRoadBtnClicked);
        HouseBtn->OnClicked.AddDynamic(this, &UMyWidget::OnHouseBtnClicked);
    }
}

void UMyWidget::OnRoadBtnClicked()
{
    GLog->Log(FString::Printf(TEXT("UMyWidget::OnRoadBtnClicked()")));
    RoadSelected = !RoadSelected;
    if (RoadSelected)
    {
        PlayerController->SpawnCustomActor(EBuildingType::E_Road);
    }
    else
    {
        PlayerController->CancelActorSpawn();
    }
}

void UMyWidget::OnHouseBtnClicked()
{
    GLog->Log(FString::Printf(TEXT("UMyWidget::OnHouseBtnClicked()")));
    HouseSelected = !HouseSelected;
    if (HouseSelected)
    {
        PlayerController->SpawnCustomActor(EBuildingType::E_House);
    }
    else
    {
        PlayerController->CancelActorSpawn();
    }
}