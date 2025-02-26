// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InteractInterface.h"
#include "GameFramework/Actor.h"
#include "Door.generated.h"

class USphereComponent;
class UStaticMeshComponent;

UCLASS()
class GAMEMECHANICS_API ADoor : public AActor, public IInteractInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADoor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere) TObjectPtr<USphereComponent> SphereCollider;
	//UPROPERTY(EditAnywhere)	TObjectPtr<USphereComponent> DoorHinge;
	UPROPERTY(EditAnywhere)	TObjectPtr<USphereComponent> DoorPivot;
	UPROPERTY(EditAnywhere) TObjectPtr<UStaticMeshComponent> Door;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Interact interface
	//virtual void Interact() override;

private:
	bool opening = false;
	bool prevOpeningState;
	float openingTimer;
	UPROPERTY(EditAnywhere, Category = "DoorAction") float openingTime;
	UPROPERTY(EditAnywhere, Category = "DoorAction") FRotator openAngle;
	UPROPERTY(EditAnywhere, Category = "DoorAction") FRotator closedAngle;
};
