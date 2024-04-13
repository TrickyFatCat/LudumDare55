// Made by Titled Goose Team during Ludum Dare 55


#include "Building.h"

#include "TrickyGameModeLibrary.h"
#include "Components/WidgetComponent.h"
#include "LudumDare55/UserInterface/BuildingMenuWidget.h"


ABuilding::ABuilding()
{
	PrimaryActorTick.bCanEverTick = false;

	SceneComponent = CreateDefaultSubobject<USceneComponent>("Root");
	SetRootComponent(SceneComponent);
	
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	MeshComponent->SetupAttachment(RootComponent);

	MenuWidgetComponent = CreateDefaultSubobject<UWidgetComponent>("MenuWidget");
	MenuWidgetComponent->SetupAttachment(RootComponent);
	SetWidgetVisibility(false);
}

void ABuilding::BeginPlay()
{
	Super::BeginPlay();

	OnReleased.AddUniqueDynamic(this, &ABuilding::HandleMouseClick);
	OnBeginCursorOver.AddUniqueDynamic(this, &ABuilding::HandleBeginCursorOver);
	OnEndCursorOver.AddUniqueDynamic(this, &ABuilding::HandleEndCursorOver);

	BuildingMenuWidget = Cast<UBuildingMenuWidget>(MenuWidgetComponent->GetWidget());
}

void ABuilding::HandleMouseClick(AActor* TouchedActor, FKey ButtonPressed)
{
	bIsSelected = true;
	UTrickyGameModeLibrary::SetMouseEventsEnabled(this, false);

	if (BuildingMenuWidget)
	{
		BuildingMenuWidget->ShowButtons();
	}
}

void ABuilding::SetWidgetVisibility(const bool bIsVisible)
{
	// ETickMode NewTickMode = bIsVisible ? ETickMode::Enabled : ETickMode::Disabled;
	// MenuWidgetComponent->SetTickMode(NewTickMode);
	MenuWidgetComponent->SetVisibility(bIsVisible, true);
}

void ABuilding::HandleBeginCursorOver(AActor* TouchedActor)
{
	SetWidgetVisibility(true);
}

void ABuilding::HandleEndCursorOver(AActor* TouchedActor)
{
	if (bIsSelected)
	{
		bIsSelected = false;
	}
	else
	{
		SetWidgetVisibility(false);
	}
}

