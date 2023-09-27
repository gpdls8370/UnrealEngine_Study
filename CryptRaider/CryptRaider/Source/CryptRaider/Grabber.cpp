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

	// ...
	
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	FHitResult Hits;
	FVector StartPos = GetComponentLocation();
	FVector EndPos = StartPos + GetForwardVector() * MaxGrabDistance;

	DrawDebugLine(GetWorld() , StartPos , EndPos , FColor::Red);

	//GetWorld()->LineTraceSingleByChannel(Hits , StartPos , EndPos , ECC_EngineTraceChannel1);

	//UE_LOG(LogTemp , Display , TEXT("%s") , *(Hits.GetActor()->GetActorNameOrLabel()));
}

