// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMechanics/Player/PlayerCharacter.h" // Why is can this .cpp access protected variables from here, but not from InputDataConfig.h ?
#include "Camera/CameraComponent.h" // to access camera component
#include "Components/SphereComponent.h" // To access and utilize sphere component

// Need the more specified location
#include "InteractInterface.h"
#include "ViewportInteractableInterface.h"
#include "Components/CapsuleComponent.h"
#include "EnhancedInput\Public\InputMappingContext.h"
#include "EnhancedInput\Public\EnhancedInputSubsystems.h"
#include "EnhancedInput\Public\EnhancedInputComponent.h"

#include "GameMechanics\DataAssets\InputDataConfig.h" // Include the data asset .h
//#include "Kismet/KismetMathLibrary.inl" // This caused build errors


// Sets default values
// Activates when starting unreal engine
APlayerCharacter::APlayerCharacter() // The constructor
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Use this for turning the camera around the player
	CameraPivot = CreateDefaultSubobject<USphereComponent>("CameraPivot");
	
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("PlayerCamera"));
	Camera->SetupAttachment(RootComponent); //CameraPivot
	Camera->bUsePawnControlRotation = true;
	//Camera->bConstrainAspectRatio = true;

	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &APlayerCharacter::OnBeginOverlapComponentEvent);
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	CapsuleCollider = GetCapsuleComponent();

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

	Input->BindAction(InputActions->IA_Interact, ETriggerEvent::Triggered, this, &APlayerCharacter::Interact); // Interact

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

void APlayerCharacter::OnBeginOverlapComponentEvent(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Overlapped with " + OtherActor->GetActorNameOrLabel()));

	if (!Cast<IInteractInterface>(OtherActor)) return;

	//OtherActor->Destroy();
}


#pragma region Advanced Input System

void APlayerCharacter::Move(const FInputActionValue& InputVector2D)
{
	printf("Move Called");

	// Moving with input

	FVector2D InputVector = InputVector2D.Get<FVector2D>();

	if (IsValid(Controller))
	{
		printf("Moving");
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
		printf("Looking");

		// Camera Movement
		AddControllerYawInput(InputVector.X);
		AddControllerPitchInput(InputVector.Y);
	}


}

void APlayerCharacter::Jump()
{
	printf("Jumping");

	ACharacter::Jump();
}

void APlayerCharacter::Interact()
{
	//printf("Interacted");


	
	TArray<AActor*> OverlappingActors;
	CapsuleCollider->GetOverlappingActors(OverlappingActors);

	TArray<AActor*> InteractableActors;
	
	AActor* closestActor = nullptr;

	for (auto OverlappingActor : OverlappingActors)
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Detected"));

		if (!Cast<IInteractInterface>(OverlappingActor)) return;

		//InteractableActors.Add(OverlappingActor);
		if (!closestActor)
			closestActor = OverlappingActor;
		else if (GetDistanceBetweenTwoActors(closestActor, this) > GetDistanceBetweenTwoActors(OverlappingActor, this))
		{
			closestActor = OverlappingActor;
		}
	}

	if (!closestActor) return;

	IInteractInterface* interactInterface = Cast<IInteractInterface>(closestActor);
	interactInterface->Interact();
	

	//closestActor->GetNativeInterfaceAddress(IInteractInterface )
	//UE_LOG(LogTemp, Log, TEXT("%s : %s"), *closestActor->GetName(), *IInteractInterface::Execute_InteractInterface(Cast<IInteractInterface>(closestActor)));
	
	

	//AActor actor;
	//std::string RandomActorName = actor.GetActorNameOrLabel();
	//std::string OverlappingActorName = OverlappingActors[0]->GetActorNameOrLabel();
	
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Interacted"));


	//bool bIsImplemented;

	/* bIsImplemented is true if OriginalObject implements UReactToTriggerInterface */
	//bIsImplemented = OriginalObject->GetClass()->ImplementsInterface(UReactToTriggerInterface::StaticClass());

	/* bIsImplemented is true if OriginalObject implements UReactToTriggerInterface */
	//bIsImplemented = OriginalObject->Implements<UReactToTriggerInterface>();

	/* ReactingObject is non-null if OriginalObject implements UReactToTriggerInterface in C++ */
	//IReactToTriggerInterface* ReactingObject = Cast<IReactToTriggerInterface>(OriginalObject);
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


float APlayerCharacter::MagnitudeOfVector3d(FVector3d vector)
{
	double x2 = vector.X * vector.X; //FMath::Square(vector.X);
	double y2 = vector.Y * vector.Y; //FMath::Square(vector.Y);
	double z2 = vector.Z * vector.Z; //FMath::Square(vector.Z);

	return FMath::Sqrt(x2 + y2 + z2);
}

float APlayerCharacter::GetDistanceBetweenTwoActors(AActor* actor1, AActor* actor2)
{
	FVector3d pos1 = actor1->GetTransform().GetLocation();
	FVector3d pos2 = actor2->GetTransform().GetLocation();

	return MagnitudeOfVector3d(pos2 - pos1);
}


