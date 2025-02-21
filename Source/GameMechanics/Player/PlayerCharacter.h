// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
//#include "GameMechanics\DataAssets\InputDataConfig.h" // Input Action data asset
#include "PlayerCharacter.generated.h"

class USphereComponent;


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

	 //UInputDataConfig; // creating the class, I need to do this for all unreal classes? They are not built in??

	

protected:
	UPROPERTY(EditAnywhere)
	TObjectPtr<USphereComponent> CameraPivot;

	// Camera variable, it is initialized in the constructor
	UPROPERTY(EditAnywhere)
	class UCameraComponent* Camera;



	// Input Mapping Context variable
	UPROPERTY(EditAnywhere, Category = "EnhancedInput") // Category is used for sorting variables in the blueprint
	class UInputMappingContext* InputMapping;
	
	
	UPROPERTY(EditAnywhere, Category = "EnhancedInput")
	class UInputDataConfig* InputActions; // Data Asset containing input actions

	void Move(const FInputActionValue& InputVector2D);
	void Look(const FInputActionValue& InputVector2D);
	void Jump();



#pragma region Example Input

	// Example Input
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	class UInputAction* ShootAction;

	UFUNCTION()
	void Shoot(const FInputActionValue& Value);

	#pragma endregion



#pragma region Initialize InputActions without DataAsset

	/*
	// Actual Input
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "EnhancedInput")
	class UInputAction* IA_Jump;
	//void Jump(const FInputActionValue& Input);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "EnhancedInput")
	class UInputAction* IA_Move;
	void Move(const FInputActionValue& InputVector2D);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "EnhancedInput")
	class UInputAction* IA_Look;
	void Look(const FInputActionValue& InputVector2D);
	*/

#pragma endregion



#pragma region Old Input System

	// Old input system
	void MoveForward(float InputValue); 
	void MoveLeft(float InputValue);

	void Turn(float InputValue);
	void Pitch(float InputValue);

#pragma endregion
};
