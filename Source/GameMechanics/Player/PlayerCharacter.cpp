// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMechanics/Player/PlayerCharacter.h" // Why is can this .cpp access protected variables from here, but not from InputDataConfig.h ?
#include "Camera/CameraComponent.h" // to access camera component

// Need the more specified location
#include "EnhancedInput\Public\InputMappingContext.h"
#include "EnhancedInput\Public\EnhancedInputSubsystems.h"
#include "EnhancedInput\Public\EnhancedInputComponent.h"

#include "GameMechanics\DataAssets\InputDataConfig.h" // Include the data asset .h



// Sets default values
// Activates when starting unreal engine
APlayerCharacter::APlayerCharacter() // The constructor
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Player Camera"));
	Camera->SetupAttachment(RootComponent);
	Camera->bUsePawnControlRotation = true;
	//Camera->bConstrainAspectRatio = true;
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);


#pragma region Advanced Input System

	// Setup input mapping context
	APlayerController* PlayerController = Cast<APlayerController>(GetController());

	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());

	Subsystem->ClearAllMappings();
	Subsystem->AddMappingContext(InputMapping, 0);


	UEnhancedInputComponent* Input = Cast<UEnhancedInputComponent>(PlayerInputComponent);


	if (!InputActions) return; // Don't read input if InputActions are invalid

	
	//Input->BindAction(ShootAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Shoot);


	// Attaching a function to an InputAction
	
	// BindAction(IA, How the IA is interacted with, Which object should do the function, The activated function)
	Input->BindAction(InputActions->IA_Move, ETriggerEvent::Triggered, this, &APlayerCharacter::Move);  // Move
	
	Input->BindAction(InputActions->IA_Look, ETriggerEvent::Triggered, this, &APlayerCharacter::Look); // Look
	
	Input->BindAction(InputActions->IA_Jump, ETriggerEvent::Triggered, this, &APlayerCharacter::Jump); // Jump

#pragma endregion


#pragma region Old Input System

	/*
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);

	PlayerInputComponent->BindAxis("MoveForward", this, &APlayerCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveLeft", this, &APlayerCharacter::MoveLeft);

	PlayerInputComponent->BindAxis("TurnCamera", this, &APlayerCharacter::Turn);
	PlayerInputComponent->BindAxis("PitchCamera", this, &APlayerCharacter::Pitch);
	*/

#pragma endregion
}


#pragma region Advanced Input System

void APlayerCharacter::Move(const FInputActionValue& InputVector2D)
{
	// Moving with input

	FVector2D InputVector = InputVector2D.Get<FVector2D>();

	if (IsValid(Controller))
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// Add Movement Input
		// Depending on if WASD pressed, it will move forwards and rightwards
		AddMovementInput(ForwardDirection, InputVector.Y);
		AddMovementInput(RightDirection, InputVector.X);

	}

}

void APlayerCharacter::Look(const FInputActionValue& InputVector2D)
{
	FVector2D InputVector = InputVector2D.Get<FVector2D>();

	if (IsValid(Controller))
	{
		// Camera Movement
		AddControllerYawInput(InputVector.X);
		AddControllerPitchInput(InputVector.Y);
	}
}

void APlayerCharacter::Jump()
{
	ACharacter::Jump();
}

#pragma endregion


#pragma region Old Input System

void APlayerCharacter::Shoot(const FInputActionValue& Value)
{
	// You can get action values like this:

	bool BoolValue = Value.Get<bool>();
	float FloatValue = Value.Get<float>();
	FVector2D Axis2DValue = Value.Get<FVector2D>();
	FVector VectorVAlue = Value.Get<FVector>();

	// Use the values down here !
}

void APlayerCharacter::MoveForward(float InputValue)
{
	FVector ForwardDirection = GetActorForwardVector();
	AddMovementInput(ForwardDirection, InputValue);
}

void APlayerCharacter::MoveLeft(float InputValue)
{
	FVector RightDirection = GetActorRightVector();
	AddMovementInput(RightDirection, -InputValue);
}

void APlayerCharacter::Turn(float InputValue)
{
	AddControllerYawInput(InputValue);
}

void APlayerCharacter::Pitch(float InputValue)
{
	AddControllerPitchInput(InputValue);
}

#pragma endregion
