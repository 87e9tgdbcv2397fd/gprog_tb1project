// Copyright Epic Games, Inc. All Rights Reserved.

#include "gprog_tb1projectCharacter.h"
#include "Animation/AnimInstance.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "EnhancedInputComponent.h"
#include "InputActionValue.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "EnemuFactory.h"
#include "Kismet/GameplayStatics.h"
#include "gprog_tb1project.h"

Agprog_tb1projectCharacter::Agprog_tb1projectCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);
	
	// Create the first person mesh that will be viewed only by this character's owner
	FirstPersonMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("First Person Mesh"));

	FirstPersonMesh->SetupAttachment(GetMesh());
	FirstPersonMesh->SetOnlyOwnerSee(true);
	FirstPersonMesh->FirstPersonPrimitiveType = EFirstPersonPrimitiveType::FirstPerson;
	FirstPersonMesh->SetCollisionProfileName(FName("NoCollision"));

	// Create the Camera Component	
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("First Person Camera"));
	FirstPersonCameraComponent->SetupAttachment(FirstPersonMesh, FName("head"));
	FirstPersonCameraComponent->SetRelativeLocationAndRotation(FVector(-2.8f, 5.89f, 0.0f), FRotator(0.0f, 90.0f, -90.0f));
	FirstPersonCameraComponent->bUsePawnControlRotation = true;
	FirstPersonCameraComponent->bEnableFirstPersonFieldOfView = true;
	FirstPersonCameraComponent->bEnableFirstPersonScale = true;
	FirstPersonCameraComponent->FirstPersonFieldOfView = 70.0f;
	FirstPersonCameraComponent->FirstPersonScale = 0.6f;

	// configure the character comps
	GetMesh()->SetOwnerNoSee(true);
	GetMesh()->FirstPersonPrimitiveType = EFirstPersonPrimitiveType::WorldSpaceRepresentation;

	GetCapsuleComponent()->SetCapsuleSize(34.0f, 96.0f);

	// Configure character movement
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;
	GetCharacterMovement()->AirControl = 0.5f;
}

void Agprog_tb1projectCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{	
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		// Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &Agprog_tb1projectCharacter::DoJumpStart);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &Agprog_tb1projectCharacter::DoJumpEnd);

		// Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &Agprog_tb1projectCharacter::MoveInput);

		// Looking/Aiming
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &Agprog_tb1projectCharacter::LookInput);
		EnhancedInputComponent->BindAction(MouseLookAction, ETriggerEvent::Triggered, this, &Agprog_tb1projectCharacter::LookInput);

		// making noise function
		EnhancedInputComponent->BindAction(MakeNoiseAction, ETriggerEvent::Started, this, &Agprog_tb1projectCharacter::MakeNoise);
		//ETriggerEvent::Started means it only fires once (when you hit N) and not repeatedly as you hold it down

		// select enemy function
		EnhancedInputComponent->BindAction(SelectEnemy1Action, ETriggerEvent::Started, this, &Agprog_tb1projectCharacter::SelectEnemy1);
		EnhancedInputComponent->BindAction(SelectEnemy2Action, ETriggerEvent::Started, this, &Agprog_tb1projectCharacter::SelectEnemy2);
		EnhancedInputComponent->BindAction(SelectEnemy3Action, ETriggerEvent::Started, this, &Agprog_tb1projectCharacter::SelectEnemy3);
		EnhancedInputComponent->BindAction(SelectEnemy4Action, ETriggerEvent::Started, this, &Agprog_tb1projectCharacter::SelectEnemy4);
		EnhancedInputComponent->BindAction(SelectEnemy5Action, ETriggerEvent::Started, this, &Agprog_tb1projectCharacter::SelectEnemy5);
		
		// kill selected enemy function
		EnhancedInputComponent->BindAction(KillEnemyAction, ETriggerEvent::Started, this, &Agprog_tb1projectCharacter::KillSelectedEnemy);
	}
	else
	{
		UE_LOG(Loggprog_tb1project, Error, TEXT("'%s' Failed to find an Enhanced Input Component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}


void Agprog_tb1projectCharacter::MoveInput(const FInputActionValue& Value)
{
	// get the Vector2D move axis
	FVector2D MovementVector = Value.Get<FVector2D>();

	// pass the axis values to the move input
	DoMove(MovementVector.X, MovementVector.Y);

}

void Agprog_tb1projectCharacter::LookInput(const FInputActionValue& Value)
{
	// get the Vector2D look axis
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	// pass the axis values to the aim input
	DoAim(LookAxisVector.X, LookAxisVector.Y);

}

void Agprog_tb1projectCharacter::DoAim(float Yaw, float Pitch)
{
	if (GetController())
	{
		// pass the rotation inputs
		AddControllerYawInput(Yaw);
		AddControllerPitchInput(Pitch);
	}
}

void Agprog_tb1projectCharacter::DoMove(float Right, float Forward)
{
	if (GetController())
	{
		// pass the move inputs
		AddMovementInput(GetActorRightVector(), Right);
		AddMovementInput(GetActorForwardVector(), Forward);
	}
}

void Agprog_tb1projectCharacter::DoJumpStart()
{
	// pass Jump to the character
	Jump();
}

void Agprog_tb1projectCharacter::DoJumpEnd()
{
	// pass StopJumping to the character
	StopJumping();
}

// makenoise function (writing what it actually does)
void Agprog_tb1projectCharacter::MakeNoise() 
{
	UE_LOG(Loggprog_tb1project, Warning, TEXT("PLEASE WORK!!!")); // text in output log for testing
	OnPlayerMadeNoise.Broadcast(GetActorLocation()); // when the event is broadcasted, get actor (player) location, and send it
}

// all the select enemy functions 
void Agprog_tb1projectCharacter::SelectEnemy1()
{
	if (factorypointer != nullptr) // if the pointer is pointing to something (aka the factory exists)...
	{
		factorypointer->selectenemy(1); // ...run the factory's function selectenemy, and input "1" to select enemy 1
	}
}

void Agprog_tb1projectCharacter::SelectEnemy2()
{
	if (factorypointer != nullptr)
	{
		factorypointer->selectenemy(2);
	}
}

void Agprog_tb1projectCharacter::SelectEnemy3()
{
	if (factorypointer != nullptr)
	{
		factorypointer->selectenemy(3);
	}
}

void Agprog_tb1projectCharacter::SelectEnemy4()
{
	if (factorypointer != nullptr)
	{
		factorypointer->selectenemy(4);
	}
}

void Agprog_tb1projectCharacter::SelectEnemy5()
{
	if (factorypointer != nullptr)
	{
		factorypointer->selectenemy(5);
	}
}

// kill selected enemy hotkey function stuff
void Agprog_tb1projectCharacter::KillSelectedEnemy()
{
	if (factorypointer != nullptr)
	{
		factorypointer->killselectedenemy();
	}
}

void Agprog_tb1projectCharacter::BeginPlay()
{
	Super::BeginPlay();

	// find an actor in the current game world from the EnemyFactory class, and put its pointer into the variable factorypointer
	factorypointer = Cast<AEnemuFactory>(
		UGameplayStatics::GetActorOfClass(GetWorld(), AEnemuFactory::StaticClass())
	);
}