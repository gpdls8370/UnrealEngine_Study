// Fill out your copyright notice in the Description page of Project Settings.


#include "TriggerComponent.h"

UTriggerComponent::UTriggerComponent()
{
	//틱을 활성화
	PrimaryComponentTick.bCanEverTick = true;
}

void UTriggerComponent::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogTemp , Display , TEXT("start"));
}

void UTriggerComponent::TickComponent(float DeltaTime , ELevelTick TickType , FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime , TickType , ThisTickFunction);

	AActor* Actor = GetAcceptableActor();
	if (Actor != nullptr) {
		//열기
		UPrimitiveComponent* Component = Cast<UPrimitiveComponent>(Actor->GetRootComponent());
		if (Component != nullptr) {
			Component->SetSimulatePhysics(false);
		}
		Actor->AttachToComponent(this , FAttachmentTransformRules::KeepWorldTransform);
		Mover->SetShouldMove(true);
	}
	else{
		//닫기
		Mover->SetShouldMove(false);
	}
}

AActor* UTriggerComponent::GetAcceptableActor() const
{
	TArray<AActor*> Actors;
	GetOverlappingActors(Actors);

	for (AActor* Actor : Actors) {
		if (Actor->ActorHasTag(AcceptableActorTag) && !Actor->ActorHasTag("Grabbed")) {
			return Actor;
		}
	}

	return nullptr;
}

void UTriggerComponent::SetMover(UMover* NewMover)
{
	Mover = NewMover;
}