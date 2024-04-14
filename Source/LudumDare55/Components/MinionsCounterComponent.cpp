// Made by Titled Goose Team during Ludum Dare 55


#include "MinionsCounterComponent.h"

#include "LudumDare55/Characters/Minion.h"


UMinionsCounterComponent::UMinionsCounterComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	bWantsInitializeComponent = true;
}

void UMinionsCounterComponent::InitializeComponent()
{
	Super::InitializeComponent();

	for (auto& Data : MinionCounters)
	{
		Data.CurrentNumber = Data.MaxNumber;
	}
}

bool UMinionsCounterComponent::IncrementCounter(TSubclassOf<AMinion> MinionClass)
{
	if (!MinionClass || MinionCounters.IsEmpty())
	{
		return false;
	}

	auto Predicate = [&](const FMinionCounterData& Data)
	{
		return Data.MinionClass == MinionClass;
	};

	if (!MinionCounters.ContainsByPredicate(Predicate))
	{
		return false;
	}

	FMinionCounterData* MinionCounterData = MinionCounters.FindByPredicate(Predicate);

	if (MinionCounterData->CurrentNumber >= MinionCounterData->MaxNumber)
	{
		return false;
	}

	MinionCounterData->CurrentNumber += 1;
	MinionCounterData->CurrentNumber = FMath::Min(MinionCounterData->CurrentNumber, MinionCounterData->MaxNumber);
	OnMinionsNumberIncreased.Broadcast(*MinionCounterData);
	return true;
}

bool UMinionsCounterComponent::DecrementCounter(TSubclassOf<AMinion> MinionClass)
{
	if (!MinionClass || MinionCounters.IsEmpty())
	{
		return false;
	}

	auto Predicate = [&](const FMinionCounterData& Data)
	{
		return Data.MinionClass == MinionClass;
	};

	if (!MinionCounters.ContainsByPredicate(Predicate))
	{
		return false;
	}

	FMinionCounterData* MinionCounterData = MinionCounters.FindByPredicate(Predicate);

	if (MinionCounterData->CurrentNumber <= 0)
	{
		return false;
	}

	MinionCounterData->CurrentNumber -= 1;
	MinionCounterData->CurrentNumber = FMath::Max(MinionCounterData->CurrentNumber, 0);
	OnMinionsNumberDecreased.Broadcast(*MinionCounterData);
	return true;
}

bool UMinionsCounterComponent::IncreaseMaxNumber(TSubclassOf<AMinion> MinionClass,
                                                 const int32 Amount,
                                                 const bool bResetCurNumber)
{
	if (Amount <= 0)
	{
		return false;
	}

	if (!MinionClass || MinionCounters.IsEmpty())
	{
		return false;
	}

	auto Predicate = [&](const FMinionCounterData& Data)
	{
		return Data.MinionClass == MinionClass;
	};

	if (!MinionCounters.ContainsByPredicate(Predicate))
	{
		return false;
	}

	FMinionCounterData* MinionCounterData = MinionCounters.FindByPredicate(Predicate);
	MinionCounterData->MaxNumber += Amount;

	if (bResetCurNumber)
	{
		MinionCounterData->CurrentNumber = MinionCounterData->MaxNumber;
	}

	OnMinionsMaxNumberIncreased.Broadcast(*MinionCounterData);
	return true;
}

bool UMinionsCounterComponent::GetMinionCounterData(TSubclassOf<AMinion> MinionClass, FMinionCounterData& OutData)
{
	if (!MinionClass || MinionCounters.IsEmpty())
	{
		return false;
	}

	auto Predicate = [&](const FMinionCounterData& Data)
	{
		return Data.MinionClass == MinionClass;
	};

	if (!MinionCounters.ContainsByPredicate(Predicate))
	{
		return false;
	}

	OutData = *MinionCounters.FindByPredicate(Predicate);
	return true;
}
