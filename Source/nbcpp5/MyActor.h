// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyActor.generated.h"

UCLASS()
class NBCPP5_API AMyActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMyActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	FVector CurrentLocation;
	void Move();
	int RandomStep();
	void CalculateDistanceAndLog(const FVector& PreviousLocation, const FVector& NewLocation);
	bool RandomEvent();

	float TotalDistance;
	bool bEventOccurred;

};
