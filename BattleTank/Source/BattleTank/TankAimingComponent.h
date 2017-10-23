// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

//Enum for aiming state
UENUM()
enum class EFiringState : uint8
{
	Reloading,
	Aiming,
	Locked
};

//Forward declarations
class UTankBarrel;
class UTankTurret;
class AProjectile;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	

	// Sets default values for this component's properties
	UTankAimingComponent();

	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable, Category = "Setup")
	void Initialise(UTankBarrel * BarrelToSet, UTankTurret * TurretToSet);

	void AimAt(FVector HitLocation);

	UFUNCTION(BlueprintCallable)
	void Fire();

	UPROPERTY(BlueprintReadOnly, Category = "State")
	EFiringState FiringState = EFiringState::Reloading;

private:

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float LaunchSpeed = 4000.f;

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float ReloadTimeInSeconds = 3;	

	UTankBarrel *Barrel = nullptr;

	UTankTurret *Turret = nullptr;
 
	void MoveBarrelTowards(FVector AimDirection);

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	TSubclassOf<AProjectile> projectileBlueprint;

	double LastFireTime = 0;

	FVector AimDirection;
		
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;

	bool IsBarrelMoving();
	
};
