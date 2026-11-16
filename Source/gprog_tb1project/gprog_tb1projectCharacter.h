// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Logging/LogMacros.h"
#include "gprog_tb1projectCharacter.generated.h"

class AEnemuFactory;
class UInputComponent;
class USkeletalMeshComponent;
class UCameraComponent;
class UInputAction;
struct FInputActionValue;

DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);

// make delegate type for the observer (this is supposed to broadcast the event)
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(
	FOnPlayerMadeNoise, // name of the event
	FVector, // it's gonna send a vector
	NoiseLocation // name of the info it gives (bc the vector is gonna be the player location)
);

/**
 *  A basic first person character
 */
UCLASS(abstract)
class Agprog_tb1projectCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Pawn mesh: first person view (arms; seen only by self) */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components", meta = (AllowPrivateAccess = "true"))
	USkeletalMeshComponent* FirstPersonMesh;

	/** First person camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components", meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FirstPersonCameraComponent;

protected:

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, Category ="Input")
	UInputAction* JumpAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, Category ="Input")
	UInputAction* MoveAction;

	/** Look Input Action */
	UPROPERTY(EditAnywhere, Category ="Input")
	class UInputAction* LookAction;

	/** Mouse Look Input Action */
	UPROPERTY(EditAnywhere, Category ="Input")
	class UInputAction* MouseLookAction;

	// hotkey stuff ("N" for noise)
	UPROPERTY(EditAnywhere, Category ="Input")
	UInputAction* MakeNoiseAction; // just like the structure of the built in stuff ^^, make a variable called makenoiseaction to hold the pointer

	// more hotkey stuff (1-5 selection)
	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* SelectEnemy1Action;

	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* SelectEnemy2Action;

	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* SelectEnemy3Action;

	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* SelectEnemy4Action;

	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* SelectEnemy5Action;

	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* KillEnemyAction;
	
public:
	Agprog_tb1projectCharacter();

protected:

	/** Called from Input Actions for movement input */
	void MoveInput(const FInputActionValue& Value);

	/** Called from Input Actions for looking input */
	void LookInput(const FInputActionValue& Value);

	/** Handles aim inputs from either controls or UI interfaces */
	UFUNCTION(BlueprintCallable, Category="Input")
	virtual void DoAim(float Yaw, float Pitch);

	/** Handles move inputs from either controls or UI interfaces */
	UFUNCTION(BlueprintCallable, Category="Input")
	virtual void DoMove(float Right, float Forward);

	/** Handles jump start inputs from either controls or UI interfaces */
	UFUNCTION(BlueprintCallable, Category="Input")
	virtual void DoJumpStart();

	/** Handles jump end inputs from either controls or UI interfaces */
	UFUNCTION(BlueprintCallable, Category="Input")
	virtual void DoJumpEnd();

	// hotkey stuff continued 
	void MakeNoise();

	// hotkey stuff for selecting/killing enemy
	void SelectEnemy1();
	void SelectEnemy2();
	void SelectEnemy3();
	void SelectEnemy4();
	void SelectEnemy5();
	void KillSelectedEnemy();

protected:

	/** Set up input action bindings */
	virtual void SetupPlayerInputComponent(UInputComponent* InputComponent) override;
	

public:

	/** Returns the first person mesh **/
	USkeletalMeshComponent* GetFirstPersonMesh() const { return FirstPersonMesh; }

	/** Returns first person camera component **/
	UCameraComponent* GetFirstPersonCameraComponent() const { return FirstPersonCameraComponent; }

	// the event that the enemies will subscribe to 
	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnPlayerMadeNoise OnPlayerMadeNoise;

protected:
	UPROPERTY()
	AEnemuFactory* factorypointer = nullptr; // pointer that will point to the factory, starts off pointing to nothing 

	virtual void BeginPlay() override;
};

