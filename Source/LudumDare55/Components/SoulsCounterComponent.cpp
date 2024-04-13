// Made by Titled Goose Team during Ludum Dare 55


#include "SoulsCounterComponent.h"

USoulsCounterComponent::USoulsCounterComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void USoulsCounterComponent::InitializeComponent()
{
	Super::InitializeComponent();
}

bool USoulsCounterComponent::AddSouls(const int32 Amount)
{
	if (Amount <= 0)
	{
		return false;
	}

	return true;
}

bool USoulsCounterComponent::SpendSouls(const int32 Amount)
{
	if (Amount <= 0)
	{
		return false;
	}

	return true;
}
