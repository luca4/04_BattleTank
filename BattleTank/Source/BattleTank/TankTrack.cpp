// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"
#include "Engine/World.h"

UTankTrack::UTankTrack()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UTankTrack::BeginPlay()
{
	OnComponentHit.AddDynamic(this, &UTankTrack::OnHit);
}

void UTankTrack::ApplySidewaysForce()
{
	//Work-out the required acceleration this frame to correct
	float SlippageSpeed = FVector::DotProduct(GetComponentVelocity(), GetRightVector());
	float DeltaTime = GetWorld()->GetDeltaSeconds();
	FVector CorrectionAcceleration = -SlippageSpeed / DeltaTime * GetRightVector();

	//Calculate and apply sideways (F = m * a)
	auto TankRoot = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());
	auto CorrectionForce = (TankRoot->GetMass() * CorrectionAcceleration) / 2; //Two tracks
	TankRoot->AddForce(CorrectionForce);
}

void UTankTrack::SetThrottle(float Throttle)
{
	CurrentThrottle = FMath::Clamp<float>(CurrentThrottle + Throttle, -1, +1);
}

void UTankTrack::DriveTrack()
{
	FVector ForceApplied = GetForwardVector() * CurrentThrottle * TrackMaxDrivingForce;
	FVector ForceLocation = GetComponentLocation();
	auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);
}

void UTankTrack::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	ApplySidewaysForce();
}


