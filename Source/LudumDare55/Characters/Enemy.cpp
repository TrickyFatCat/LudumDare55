// Made by Titled Goose Team during Ludum Dare 55


#include "Enemy.h"

#include "LudumDare55/Components/HitPointsComponent.h"


AEnemy::AEnemy()
{
	PrimaryActorTick.bCanEverTick = true;

	HitPointsComponent = CreateDefaultSubobject<UHitPointsComponent>("HitPoints");
}

void AEnemy::BeginPlay()
{
	Super::BeginPlay();

	if (!BonesToHide.IsEmpty())
	{
		for (auto& BoneName : BonesToHide)
		{
			GetMesh()->HideBoneByName(BoneName, PBO_None);
		}
	}
}

void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


