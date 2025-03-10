// Fill out your copyright notice in the Description page of Project Settings.


#include "CoinPickup.h"
#include "GameFramework/Character.h"
#include "Components/SphereComponent.h"
#include "DynamicMesh/ColliderMesh.h"


// Sets default values
ACoinPickup::ACoinPickup()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	ColliderComponent = CreateDefaultSubobject<USphereComponent>("ColliderComponent"); // Create sphere in the blueprint
	SetRootComponent(ColliderComponent); // Place under the root component

	// All these are changes to the ColliderComponent variables in the blueprint
	ColliderComponent->SetGenerateOverlapEvents(true);	
	ColliderComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly); // Query is required for overlap
	ColliderComponent->SetCollisionResponseToAllChannels(ECR_Ignore); // Everything except for the pawn to ignore
	ColliderComponent->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap); // Other pawns can also pick up the items

	// When an overlap event happens for ColliderComponent, "this" executes "&ACoinPickup::OnBeginOverlapComponentEvent"
	ColliderComponent->OnComponentBeginOverlap.AddDynamic(this, &ACoinPickup::OnBeginOverlapComponentEvent);
	//ColliderComponent->OnComponentBeginOverlap.(&ACoinPickup::OnBeginOverlapComponentEvent);

	//Creates and assigns MeshComponent, but does not attach
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	MeshComponent->SetupAttachment(ColliderComponent);
	MeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	// Avoid checking for unnecessary calls
	// These are also changes in variables (for the MeshComponent) in the blueprint. (Not necessary to be done in code)
	MeshComponent->SetCollisionResponseToAllChannels(ECR_Ignore);
	MeshComponent->SetGenerateOverlapEvents(false);
}


void ACoinPickup::OnBeginOverlapComponentEvent(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, 
	UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Overlapped"));
	
	// If Actor is not a character
	if (!Cast<ACharacter>(OtherActor)) return; // TODO: This should be done in PlayerCharacter to only activate when they overlap
	

	if (OnCoinPickup.IsBound()) // Check if it is bound, and broadcast coin has been picked up
	{
		OnCoinPickup.Broadcast();
	}

	Destroy();
}

// Called when the game starts or when spawned


// Called every frame


