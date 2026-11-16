// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/StaticMeshComponent.h" // for the static meshes
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EnemyAbstract.generated.h"

class Agprog_tb1projectCharacter; // so the enemies can subscribe to the player's event broadcast

UCLASS(Abstract)
class GPROG_TB1PROJECT_API AEnemyAbstract : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEnemyAbstract();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	float hearingrange = 100.0f; // protected variable so children can access. hearingrange is a float they will all have

	UFUNCTION()
	void HearNoise(FVector NoiseLocation); // declare a function HearNoise that accepts a FVector input called NoiseLocation

	void ChangeColor(); // function that the enemy will call inside hearnoise 

	void RevertColor(); // function that the enemy will call to revert its color back to normal

public:
	UPROPERTY(VisibleAnywhere, Category = "Enemy") // for the static meshes. both children will inherit this
	UStaticMeshComponent* EnemyMesh;

	// make a pointer for the enemies' individual instances of the material
	UPROPERTY()
	UMaterialInstanceDynamic* EnemyDynamicMaterial;

	UPROPERTY()
	FLinearColor OriginalColor; // OriginalColor (variable) stores the original color of the enemy, whether green (slime) or black (evilguy)

	UPROPERTY(EditAnywhere, Category = "Enemy")
	FLinearColor ReactionColor = FLinearColor::Red; // ReactionColor (variable) stores the color it's gonna turn (red)

	void Subscribe(Agprog_tb1projectCharacter* Player); // subscription function. receives pointer to player 
	// has to be public bc enemyfactory is gonna use it

protected:
	FTimerHandle ColorTimerHandle; // timer handle for the enemies to revert color
	// this allows the timer to restart from 5 secs if they get multiple noises

	int32 enemyID = 0; // unique enemy id variable to identify each enemy

public:
	void setenemyID(int32 newID); // setter function so enemyID can be changed
	int32 getenemyID() const; // getter function. const means it can't be changed
};
