// Fill out your copyright notice in the Description page of Project Settings.


#include "Door.h"

#include "AnimationCoreLibrary.h"
#include "FrameTypes.h"
#include "Components/SphereComponent.h"

// Sets default values
ADoor::ADoor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SphereCollider = CreateDefaultSubobject<USphereComponent>("InteractCollider");
	SphereCollider->SetupAttachment(RootComponent);
	SphereCollider->SetSphereRadius(200);

	//DoorHinge = CreateDefaultSubobject<USphereComponent>("DoorHinge");
	//DoorHinge->SetupAttachment(RootComponent);

	DoorPivot = CreateDefaultSubobject<USphereComponent>("DoorPivot");
	DoorPivot->SetupAttachment(SphereCollider);

	Door = CreateDefaultSubobject<UStaticMeshComponent>("Door");
	Door->SetupAttachment(DoorPivot);

}

// Called when the game starts or when spawned
void ADoor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Has been interacted with this frame
	bool doorActivated = opening != prevOpeningState; 

	// If it has been activated this frame (activating the if statement when openingTimer is at the extremes) or when openingTimer is between the values
	if (doorActivated || (0 < openingTimer && openingTimer < openingTime)) 
	{
		openingTimer += DeltaTime * opening ? 1 : -1;
		openingTimer = FMath::Clamp(openingTimer, 0, openingTime);

		// Lerp doorAngle with openingTimer
		//currentAngle = FMath::Lerp(openAngle, closedAngle, openingTimer / openingTime);

		// Apply currentAngle to pivot object
		//DoorHinge->GetRelativeTransform()

		//FRotator rot1 = FRotator(closedAngle, 0, 0);
		//FRotator rot2 = FRotator(openAngle, 0, 0);

		//AnimationCore::QuatFromEuler()FQuat::Euler(0, 0, 0);
		//FRotator newRotation = FQuat::Slerp(rot1, rot1, openingTimer / openingTime);

		float alpha = openingTimer / openingTime;
		FRotator newRotation = FMath::Lerp(closedAngle, openAngle, alpha);
		//DoorHinge->SetRelativeRotation(newRotation);
	}
	
	prevOpeningState = opening;
}


void ADoor::Interact()
{
	opening = !opening;

	//return opening;
}
