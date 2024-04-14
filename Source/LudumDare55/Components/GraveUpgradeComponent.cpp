// Made by Titled Goose Team during Ludum Dare 55


#include "GraveUpgradeComponent.h"

#include "MinionsCounterComponent.h"
#include "SoulsCounterComponent.h"
#include "Kismet/GameplayStatics.h"


UGraveUpgradeComponent::UGraveUpgradeComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UGraveUpgradeComponent::BeginPlay()
{
	Super::BeginPlay();

	const APawn* Pawn = UGameplayStatics::GetPlayerPawn(this, 0);

	SoulsCounterComponent = Pawn->GetComponentByClass<USoulsCounterComponent>();
	MinionsCounterComponent = Pawn->GetComponentByClass<UMinionsCounterComponent>();

	UpgradeCost = UpgradeTable.AsInteger(InitialLevel);

	if (InitialLevel > 0)
	{
	}
}

bool UGraveUpgradeComponent::Upgrade()
{
	if (!SoulsCounterComponent || MinionsCounterComponent)
	{
		return false;
	}

	if (SoulsCounterComponent->GetSouls() < UpgradeCost)
	{
		return false;
	}

	SoulsCounterComponent->SpendSouls(UpgradeCost);
	MinionsCounterComponent->IncreaseMaxNumber(MinionClass, 1);
	Level += 1;
	UpgradeCost = UpgradeTable.AsInteger(Level);
	OnGraveUpgraded.Broadcast(MinionClass, Level, UpgradeCost, SoulsCounterComponent->GetSouls() < UpgradeCost);
	return true;
}
