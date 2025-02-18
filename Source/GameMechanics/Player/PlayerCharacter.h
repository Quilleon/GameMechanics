// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PlayerCharacter.generated.h"

UCLASS()
class GAMEMECHANICS_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	// Adding components to character, is initialized in the constructor
	UPROPERTY(EditAnywhere)
	class UCameraComponent* Camera;

	UPROPERTY(EditAnywhere, Category = "EnhancedInput")
	class UInputMappingContext* InputMapping;

	// Example Input
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	class UInputAction* ShootAction;

	UFUNCTION()
	void Shoot(const FInputActionValue& Value);


	// Actual Input
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	class UInputAction* IA_Jump;
	//void Jump(const FInputActionValue& Input);

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	class UInputAction* IA_Move;
	void Move(const FInputActionValue& InputVector2D);

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	class UInputAction* IA_Look;
	void Look(const FInputActionValue& InputVector2D);

	
	//void Jump(const FInputActionValue& Value);


	// Old input system
	void MoveForward(float InputValue); 
	void MoveLeft(float InputValue);

	void Turn(float InputValue);
	void Pitch(float InputValue);
};
