#include "UI/MyWidget.h"
#include "MyPlayerController.h"

#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/EditableTextBox.h"
#include "Components/Image.h"
#include "Components/CanvasPanelSlot.h"
#include "Blueprint/WidgetLayoutLibrary.h"

void UMyWidget::NativeConstruct()
{
    Super::NativeConstruct();
    GLog->Log(FString::Printf(TEXT("UMyWidget::NativeConstruct()")));

    PlayerController = Cast<AMyPlayerController>(GetOwningPlayer());
    MyTextView->SetVisibility(ESlateVisibility::Hidden);
    MyEditableTextField->SetVisibility(ESlateVisibility::Hidden);
    MyImage->SetVisibility(ESlateVisibility::Hidden);
    //Bind the button click event
    if (RoadBtn != nullptr && HouseBtn != nullptr)
    {
        RoadBtn->OnClicked.AddDynamic(this, &UMyWidget::OnRoadBtnClicked);
        HouseBtn->OnClicked.AddDynamic(this, &UMyWidget::OnHouseBtnClicked);
    }
}

void UMyWidget::OnRoadBtnClicked()
{
    GLog->Log(FString::Printf(TEXT("UMyWidget::OnRoadBtnClicked()")));
    //Reset House Selection
    if (HouseSelected) { OnHouseBtnClicked(); }

    RoadSelected = !RoadSelected;

    if (RoadSelected)
    {
        PlayerController->SetSpawnType(EBuildingType::E_Road);
        MyImage->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
        static const FVector2D& ButtonPosition = (UWidgetLayoutLibrary::SlotAsCanvasSlot(RoadBtn))->GetPosition();
        static const FVector2D& ButtonPositionPadded = FVector2D(ButtonPosition.X - 50, ButtonPosition.Y - 50);
        (UWidgetLayoutLibrary::SlotAsCanvasSlot(MyImage))->SetPosition(ButtonPositionPadded);
    }
    else if (!RoadSelected)
    {
        PlayerController->SetSpawnType(EBuildingType::E_None);
        MyImage->SetVisibility(ESlateVisibility::Hidden);
        PlayerController->CancelActorSpawn();
    }
}

void UMyWidget::OnHouseBtnClicked()
{
    GLog->Log(FString::Printf(TEXT("UMyWidget::OnHouseBtnClicked()")));
    //Reset Road Selection
    if (RoadSelected) { OnRoadBtnClicked(); }

    HouseSelected = !HouseSelected;

    if (HouseSelected)
    {
        MyImage->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
        static const FVector2D& ButtonPosition = (UWidgetLayoutLibrary::SlotAsCanvasSlot(HouseBtn))->GetPosition();
        static const FVector2D& ButtonPositionPadded = FVector2D(ButtonPosition.X - 50, ButtonPosition.Y - 50);
        (UWidgetLayoutLibrary::SlotAsCanvasSlot(MyImage))->SetPosition(ButtonPositionPadded);
        PlayerController->SetSpawnType(EBuildingType::E_House);
    }
    else if (!HouseSelected)
    {
        MyImage->SetVisibility(ESlateVisibility::Hidden);
        PlayerController->SetSpawnType(EBuildingType::E_None);
        PlayerController->CancelActorSpawn();
    }
}