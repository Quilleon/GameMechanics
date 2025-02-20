// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CoinPickup.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnCoinPickupDelegate);

class UStaticMeshComponent;
class USphereComponent;

UCLASS()
class GAMEMECHANICS_API ACoinPickup : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACoinPickup();

	UPROPERTY(BlueprintAssignable, Category="Coin Pickup")
	FOnCoinPickupDelegate OnCoinPickup;

	//UFUNCTION()
	void OnBeginOverlapComponentEvent(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

protected:
	// Called when the game starts or when spawned
	UPROPERTY(EditAnywhere, Category = "Coin Pickup")
	TObjectPtr<UStaticMeshComponent> MeshComponent;

	UPROPERTY(EditAnywhere, Category = "Coin Pickup")
	TObjectPtr<USphereComponent> ColliderComponent;


public:	
	// Called every frame

};
