// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"


void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();

	ATank* Tank = GetControlledTank();
	if (Tank)
	{
		UE_LOG(LogTemp, Warning, TEXT("Tank possessed: %s"), *Tank->GetName())
	}
	else
		UE_LOG(LogTemp, Warning, TEXT("Tank not possessed"))
}

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AimTowardsCrosshair();
}

ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

void ATankPlayerController::AimTowardsCrosshair()
{
	if (!GetControlledTank()) return;

	FVector HitLocation;
	if (GetSightRayHitLocation(HitLocation))
	{
		UE_LOG(LogTemp, Warning, TEXT("HitLocation: %s"), *HitLocation.ToString())

		//if it hits the landscape
			//Tell controlled tank to aim at this point
	}

}

bool ATankPlayerController::GetSightRayHitLocation(FVector &OutHitLocation) const
{

	return false;
}




