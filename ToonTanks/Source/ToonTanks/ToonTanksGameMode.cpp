// Fill out your copyright notice in the Description page of Project Settings.


#include "ToonTanksGameMode.h"
#include <Kismet/GameplayStatics.h>
#include "BasePawn.h"
#include "Tank.h"

void AToonTanksGameMode::ActorDied(AActor* DeadActor)
{
	if (ABasePawn* BasePawn = Cast<ABasePawn>(DeadActor))
	{
		BasePawn->HandleDestruction();
	}
	 
	if (DeadActor == Tank)
	{
		if (APlayerController* TankController = Tank->GetPlayerController())
		{
			Tank->DisableInput(TankController);
			TankController->bShowMouseCursor = false;
		}
	}
}

void AToonTanksGameMode::BeginPlay()
{
	Super::BeginPlay();

	Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));
}