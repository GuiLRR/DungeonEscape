// Fill out your copyright notice in the Description page of Project Settings.


#include "TriggerComponent.h"

UTriggerComponent::UTriggerComponent()
{
		PrimaryComponentTick.bCanEverTick = true;
}

void UTriggerComponent::BeginPlay()
{
	Super::BeginPlay();
	
	if (moverActor)
	{
		mover =  moverActor->FindComponentByClass<UMover>();	
		if(mover)
		{
			UE_LOG(LogTemp, Display, TEXT("Found mover component"));
		
		}
	}
	if (isPressurePlate)
	{
		
		OnComponentBeginOverlap.AddDynamic(this, &UTriggerComponent::OnOverlapBegin);
		OnComponentEndOverlap.AddDynamic(this, &UTriggerComponent::OnOverLapEnd);
	}
}

void UTriggerComponent::TickComponent(float DeltaTime, ELevelTick TickType,
	FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UTriggerComponent::Trigger(AActor* OtherActor, bool newtriggerValue)
{
	bool hasTag = OtherActor-> ActorHasTag("pressurePlateActivation");
	
	
	
	if(mover)
	{
		mover-> SetShouldMove(newtriggerValue);	
	}
}

void UTriggerComponent::OnOverlapBegin(UPrimitiveComponent* OverLappedComp, AActor* OtherActor,
                                       UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	++activationCount;
	if(isTriggered && activationCount <0) return;
	Trigger(OtherActor, true);
}

void UTriggerComponent::OnOverLapEnd(UPrimitiveComponent* OverLappedComp, AActor* OtherActor,
                                     UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	--activationCount;
	
	if(!isTriggered && activationCount >1) return;
	Trigger(OtherActor, false);	
}
