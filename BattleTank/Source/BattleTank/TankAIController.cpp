// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "Engine/World.h"

ATankAIController::ATankAIController()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (GetPlayerTank())
	{
		//TODO move towards the player

		//Aim towards the player
		GetControlledTank()->AimAt(GetPlayerTank()->GetActorLocation());

		//fire if ready
	}
}

ATank* ATankAIController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

	ATank *Tank = GetControlledTank();
	ATank *PlayerTank = GetPlayerTank();

	if(Tank)
		UE_LOG(LogTemp, Warning, TEXT("Tank possessed by AI: %s"), *Tank->GetName())
	else
		UE_LOG(LogTemp, Warning, TEXT("Tank not possessed by AI"), *Tank->GetName())

	if (PlayerTank)
		UE_LOG(LogTemp, Warning, TEXT("Playertank: %s"), *PlayerTank->GetName())
}

ATank* ATankAIController::GetPlayerTank() const
{
	return Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
}
