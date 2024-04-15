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

	SoulsCounterComponent->OnSoulsAdded.AddDynamic(this, &UGraveUpgradeComponent::HandleSoulsNumberChanged);
	SoulsCounterComponent->OnSoulsSpent.AddDynamic(this, &UGraveUpgradeComponent::HandleSoulsNumberChanged);
	Level = InitialLevel;
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

	if (CanUpgrade())
	{
		return false;
	}

	SoulsCounterComponent->SpendSouls(UpgradeCost);
	MinionsCounterComponent->IncreaseMaxNumber(MinionClass, 1);
	Level += 1;
	UpgradeCost = UpgradeTable.AsInteger(Level);
	OnGraveUpgraded.Broadcast(MinionClass, Level, UpgradeCost, CanUpgrade());
	return true;
}

bool UGraveUpgradeComponent::CanUpgrade() const
{
	return SoulsCounterComponent->GetSouls() >= UpgradeCost;
}

void UGraveUpgradeComponent::HandleSoulsNumberChanged(USoulsCounterComponent* Component,
                                                      int32 NewSouls,
                                                      int32 DeltaSouls)
{
	if (NewSouls >= UpgradeCost)
	{
		OnUpgradeUnlocked.Broadcast();
	}
	else
	{
		OnUpgradeUnlocked.Broadcast();
	}
}
