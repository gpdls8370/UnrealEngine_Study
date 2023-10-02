// Fill out your copyright notice in the Description page of Project Settings.


#include "Grabber.h"

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();

	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (PhysicsHandle == nullptr) return;

	if (PhysicsHandle->GetGrabbedComponent() != nullptr) {
		PhysicsHandle->SetTargetLocationAndRotation(
	GetComponentLocation() + GetForwardVector() * HoldDistance ,
	GetComponentRotation()
		);
	}
}

void UGrabber::Grab()
{
	if (PhysicsHandle == nullptr) return;

	FHitResult Hit;
	bool HasHit = GetGrabbableInReach(Hit);
	if (HasHit) {
		UPrimitiveComponent* HitComponent = Hit.GetComponent();
		HitComponent->WakeAllRigidBodies();
		PhysicsHandle->GrabComponentAtLocationWithRotation(
			HitComponent ,
			NAME_None,
			Hit.ImpactPoint ,
			GetComponentRotation()
		);
	}
}

void UGrabber::Release(){
	if (PhysicsHandle == nullptr) return;

	if (PhysicsHandle->GetGrabbedComponent() != nullptr){
		PhysicsHandle->GetGrabbedComponent()->WakeAllRigidBodies();
		PhysicsHandle->ReleaseComponent();
	}
}

bool UGrabber::GetGrabbableInReach(FHitResult& OutHit) const {
	FVector StartPos = GetComponentLocation();
	FVector EndPos = StartPos + GetForwardVector() * MaxGrabDistance;

	//DrawDebugLine(GetWorld() , StartPos , EndPos , FColor::Red);

	return GetWorld()->SweepSingleByChannel(
		OutHit ,
		StartPos , EndPos ,
		FQuat::Identity ,
		ECC_GameTraceChannel2 ,
		FCollisionShape::MakeSphere(GrabRadius)
	);
}