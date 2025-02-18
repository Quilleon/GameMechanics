// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMechanics/Player/PlayerCharacter.h"
#include "Camera/CameraComponent.h"

// Need the full location for some reason
#include "G:\Epic Games\UE_5.5\Engine\Plugins\EnhancedInput\Source\EnhancedInput\Public\InputMappingContext.h"
#include "G:\Epic Games\UE_5.5\Engine\Plugins\EnhancedInput\Source\EnhancedInput\Public\EnhancedInputSubsystems.h"
#include "G:\Epic Games\UE_5.5\Engine\Plugins\EnhancedInput\Source\EnhancedInput\Public\EnhancedInputComponent.h"



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


	// Setup input mapping context
	APlayerController* PlayerController = Cast<APlayerController>(GetController());

	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());

	Subsystem->ClearAllMappings();
	Subsystem->AddMappingContext(InputMapping, 0);


	UEnhancedInputComponent* Input = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	Input->BindAction(ShootAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Shoot);



	/*
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		// Get local player subsystem
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			// Add Input context
			Subsystem->AddMappingContext(InputMapping, 0);
		}
	}
	*/

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);

	PlayerInputComponent->BindAxis("MoveForward", this, &APlayerCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveLeft", this, &APlayerCharacter::MoveLeft);

	PlayerInputComponent->BindAxis("TurnCamera", this, &APlayerCharacter::Turn);
	PlayerInputComponent->BindAxis("PitchCamera", this, &APlayerCharacter::Pitch);
}

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
