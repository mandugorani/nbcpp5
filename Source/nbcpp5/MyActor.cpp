// Fill out your copyright notice in the Description page of Project Settings.


#include "MyActor.h"
#include "Math/UnrealMathUtility.h"
#include "Components/InputComponent.h"
#include "Engine/Engine.h"

// Sets default values
AMyActor::AMyActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	AutoReceiveInput = EAutoReceiveInput::Player0;
	PrimaryActorTick.bCanEverTick = true;
	CurrentLocation = FVector(0, 0, 0);
	TotalDistance = 0;
	bEventOccurred = false;
}

// Called when the game starts or when spawned
void AMyActor::BeginPlay()
{
	Super::BeginPlay();

	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	if (PlayerController)
	{
		EnableInput(PlayerController);
		if (InputComponent != nullptr)
		{
			InputComponent->BindAction("MoveActor", IE_Pressed, this, &AMyActor::Move);
		}
	}

	UE_LOG(LogTemp, Log, TEXT("Total Distance: %f"), TotalDistance);
	UE_LOG(LogTemp, Log, TEXT("Event Occurred: %s"), bEventOccurred ? TEXT("True") : TEXT("False"));
	UE_LOG(LogTemp, Log, TEXT("HOTRELOAD_TEST"));
}

void AMyActor::Move()
{
	FVector PreviousLocation = CurrentLocation;
	for (int i = 0; i < 10; i++)
	{
		PreviousLocation = CurrentLocation;
		CurrentLocation.X += RandomStep();
		CurrentLocation.Y += RandomStep();

		SetActorLocation(CurrentLocation);

		UE_LOG(LogTemp, Log, TEXT("Moved to location: (%f, %f)"), CurrentLocation.X, CurrentLocation.Y);

		CalculateDistanceAndLog(PreviousLocation, CurrentLocation);

		if (RandomEvent())
		{
			UE_LOG(LogTemp, Log, TEXT("Random Event Occurred at step %d!"), i + 1);
			bEventOccurred = true;
			UE_LOG(LogTemp, Log, TEXT("Total Distance: %f"), TotalDistance);
		}
		else {
			UE_LOG(LogTemp, Log, TEXT("No Random Event Occurred at step %d!"), i + 1);
			UE_LOG(LogTemp, Log, TEXT("Total Distance: %f"), TotalDistance);
		}
	}
}

int AMyActor::RandomStep()
{
	return FMath::RandRange(0, 1);
}

void AMyActor::CalculateDistanceAndLog(const FVector& PreviousLocation, const FVector& NewLocation)
{
	float Distance = FVector::Dist(PreviousLocation, NewLocation);
	TotalDistance += Distance;
	UE_LOG(LogTemp, Log, TEXT("Distance from previous location: %f"), Distance);
}

bool AMyActor::RandomEvent()
{
	return FMath::RandRange(0, 1) == 1;
}