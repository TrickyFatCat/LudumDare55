// Made by Titled Goose Team during Ludum Dare 55


#include "BuildingMenuWidget.h"

#include "BuildingButtonWidget.h"
#include "ButtonWidget.h"
#include "TrickyGameModeLibrary.h"
#include "Components/HorizontalBox.h"
#include "Components/Spacer.h"
#include "Kismet/GameplayStatics.h"

void UBuildingMenuWidget::NativeOnInitialized()
{
	if (Button_Quit)
	{
		Button_Quit->OnButtonClicked.AddUniqueDynamic(this, &UBuildingMenuWidget::HandleButtonClicked);
		Button_Quit->SetOwningBuilding(OwningBuilding);
	}

	GenerateButtons();
	Super::NativeOnInitialized();
}

void UBuildingMenuWidget::NativePreConstruct()
{
	Super::NativePreConstruct();

	if (IsDesignTime())
	{
		GenerateButtons();
	}
}

void UBuildingMenuWidget::ShowButtons()
{
	SetButtonsVisibility(true);
}

void UBuildingMenuWidget::SetOwningBuilding(ABuilding* Building)
{
	OwningBuilding = Building;
	
	if (!Buttons.IsEmpty())
	{
		for (auto Button : Buttons)
		{
			if (!Button)
			{
				continue;
			}

			Button->SetOwningBuilding(OwningBuilding);
		}
	}
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

void UBuildingMenuWidget::GenerateButtons()
{
	if (!HorizontalBox_Buttons)
	{
		return;
	}

	HorizontalBox_Buttons->ClearChildren();
	Buttons.Empty();

	if (ButtonClasses.IsEmpty())
	{
		return;
	}

	for (auto Button : ButtonClasses)
	{
		if (!Button)
		{
			continue;
		}

		UBuildingButtonWidget* NewButton = CreateWidget<UBuildingButtonWidget>(this, Button);
		NewButton->SetVisibility(ESlateVisibility::Hidden);
		HorizontalBox_Buttons->AddChildToHorizontalBox(NewButton);
		Buttons.Add(NewButton);

		USpacer* Spacer = NewObject<USpacer>(this, USpacer::StaticClass());
		Spacer->SetSize(FVector2D{0.f, SpaceBetweenButtons});
		HorizontalBox_Buttons->AddChildToHorizontalBox(Spacer);
	}
}
