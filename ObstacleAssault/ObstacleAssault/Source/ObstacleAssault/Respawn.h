// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "Respawn.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class OBSTACLEASSAULT_API URespawn : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	URespawn();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	FVector StartPosition;
	UPrimitiveComponent* PrimitiveComponent;
	float NowTime = 0;

	UPROPERTY(EditAnywhere)
	float RespawnTime;

	void StopActor();
};
