// Made by Titled Goose Team during Ludum Dare 55


#include "BuildingMenuWidget.h"

#include "ButtonWidget.h"
#include "TrickyGameModeLibrary.h"
#include "Components/HorizontalBox.h"
#include "Components/Spacer.h"
#include "Kismet/GameplayStatics.h"

void UBuildingMenuWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if (Button_Quit)
	{
		Button_Quit->OnButtonClicked.AddUniqueDynamic(this, &UBuildingMenuWidget::HandleButtonClicked);
	}
}

void UBuildingMenuWidget::NativePreConstruct()
{
	Super::NativePreConstruct();

	if (!HorizontalBox_Buttons)
	{
		return;
	}

	HorizontalBox_Buttons->ClearChildren();
	Buttons.Empty();

	if (Buttons.IsEmpty())
	{
		return;
	}

	for (auto Button : ButtonClasses)
	{
		if (!Button)
		{
			continue;
		}

		UButtonWidget* NewButton = CreateWidget<UButtonWidget>(this, Button);
		USpacer* Spacer = NewObject<USpacer>(this, USpacer::StaticClass());
		Spacer->SetSize(FVector2D{0.f, SpaceBetweenButtons});
		HorizontalBox_Buttons->AddChildToHorizontalBox(NewButton);
		HorizontalBox_Buttons->AddChildToHorizontalBox(Spacer);
		Buttons.Add(NewButton);
	}
}

void UBuildingMenuWidget::ShowButtons()
{
	SetButtonsVisibility(true);
}


void UBuildingMenuWidget::HandleButtonClicked(UButtonWidget* ButtonWidget)
{
	SetButtonsVisibility(false);
	UTrickyGameModeLibrary::SetMouseEventsEnabled(this, true);
}

void UBuildingMenuWidget::SetButtonsVisibility(const bool bIsVisible)
{
	ESlateVisibility NewVisibility = bIsVisible ? ESlateVisibility::Visible : ESlateVisibility::Hidden;
	Button_Quit->SetVisibility(NewVisibility);

	if (Buttons.IsEmpty())
	{
		return;
	}

	for (auto Button : Buttons)
	{
		if (!Button)
		{
			continue;
		}

		Button->SetVisibility(NewVisibility);
	}
}
