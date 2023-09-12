// Fill out your copyright notice in the Description page of Project Settings.

#include "MovingPlatform.h"

// Sets default values
AMovingPlatform::AMovingPlatform()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMovingPlatform::BeginPlay()
{
	Super::BeginPlay();

	StartLocation = GetActorLocation();

	FString MyString = "My String Value";

	UE_LOG(LogTemp , Display , TEXT("Here's My String : %s"), *MyString);
}

// Called every frame
void AMovingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// 플랫폼 앞으로 이동
		// 현재 위치 얻기
	FVector CurrentLocation = GetActorLocation();
		// 앞쪽으로 벡터 더해주기
	CurrentLocation += PlatformVelocity * DeltaTime;
		// 위치 지정하기
	SetActorLocation(CurrentLocation);

	// 플랫폼이 너무 멀리 가면 방향을 반대로
		// 플랫폼 이동한 거리 확인
	float dist = FVector::Dist(StartLocation, CurrentLocation);
		// 거리가 멀면 방향을 반대로
	if (dist > MoveDistance)
	{
		FString text = GetName() + " overshoot " + FString::SanitizeFloat(dist - MoveDistance);

		UE_LOG(LogTemp , Display , TEXT("%s") , *text);

		FVector MoveDiraction = PlatformVelocity.GetSafeNormal();
		StartLocation = StartLocation + MoveDiraction * MoveDistance;
		SetActorLocation(StartLocation);

		PlatformVelocity = -PlatformVelocity;
	}
}

