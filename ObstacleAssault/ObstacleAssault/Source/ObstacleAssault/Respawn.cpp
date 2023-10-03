// Fill out your copyright notice in the Description page of Project Settings.


#include "Respawn.h"

// Sets default values for this component's properties
URespawn::URespawn()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void URespawn::BeginPlay()
{
	Super::BeginPlay();

	StartPosition = GetOwner()->GetActorLocation();
	PrimitiveComponent = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
}


void URespawn::TickComponent(float DeltaTime , ELevelTick TickType , FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime , TickType , ThisTickFunction);

	NowTime += DeltaTime;

	if (NowTime > RespawnTime) {
		GetOwner()->SetActorLocation(StartPosition);
		PrimitiveComponent->SetSimulatePhysics(false);
		PrimitiveComponent->SetSimulatePhysics(true);
		NowTime = 0;
	}
}

