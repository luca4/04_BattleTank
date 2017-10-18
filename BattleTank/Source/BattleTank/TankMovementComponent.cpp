// Fill out your copyright notice in the Description page of Project Settings.

#include "TankMovementComponent.h"
#include "TankTrack.h"

void UTankMovementComponent::Initialise(UTankTrack* LeftTrackToSet, UTankTrack* RightTrackToSet)
{
	LeftTrack = LeftTrackToSet;
	RightTrack = RightTrackToSet;
}

void UTankMovementComponent::IntendMoveForward(float Throw)
{
	if (!LeftTrack || !RightTrack) return;
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(Throw);
}

void UTankMovementComponent::IntendTurnRight(float Throw)
{
	if (!ensure(LeftTrack && RightTrack)) return;
	if (Throw > 0)
	{
		LeftTrack->SetThrottle(Throw);
		RightTrack->SetThrottle(-Throw);
	}
	else
	{
		LeftTrack->SetThrottle(Throw);
		RightTrack->SetThrottle(-Throw);
	}
}

void UTankMovementComponent::RequestDirectMove(const FVector & MoveVelocity, bool bForceMaxSpeed)
{
	FVector TankForward = GetOwner()->GetActorForwardVector();
	FVector AIForwardIntention = MoveVelocity.GetSafeNormal();
	
	float ForwardThrow = FVector::DotProduct(TankForward, AIForwardIntention);
	IntendMoveForward(ForwardThrow);

	float TurnThrow = FVector::CrossProduct(AIForwardIntention, TankForward).Z;
	IntendTurnRight(TurnThrow);

}