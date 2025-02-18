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

	ColliderComponent = CreateDefaultSubobject<USphereComponent>("ColliderComponent");
	SetRootComponent(ColliderComponent);
	ColliderComponent->SetGenerateOverlapEvents(true);

	// Query is required for overlap
	ColliderComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	// Everything except for the pawn to ignore
	ColliderComponent->SetCollisionResponseToAllChannels(ECR_Ignore);
	ColliderComponent->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap); // Other pawns can also pick up the items

	//Creates and assigns MeshComponent, but does not attach
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	MeshComponent->SetupAttachment(ColliderComponent);
	MeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	//Avoid checking for unnecessary calls
	MeshComponent->SetCollisionResponseToAllChannels(ECR_Ignore);
	MeshComponent -> SetGenerateOverlapEvents(false);
}

void ACoinPickup::OnBeginOverlapComponentEvent(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// If Actor is not a character
	if (!Cast<ACharacter>(OtherActor)) return;

	// Check is it is bound, and broadcast coin has been picked up

	if (OnCoinPickup.IsBound())
	{
		OnCoinPickup.Broadcast();
	}

	Destroy();
}

// Called when the game starts or when spawned


// Called every frame


