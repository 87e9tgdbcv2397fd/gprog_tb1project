// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine/EngineTypes.h"
#include "EnemyAbstract.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Containers/List.h"
#include "EnemuFactory.generated.h"

UCLASS()
class GPROG_TB1PROJECT_API AEnemuFactory : public AActor
{
	GENERATED_BODY()
	
public:	
	void spawnrandomenemy(); // declare a function. how it works is in .cpp

	UPROPERTY(EditAnywhere, Category = "Spawning")
	float SpawnRadius = 500.0f; // how far away from the enemyfactory actor can it spawn stuff?

	virtual void BeginPlay() override; // so i can call the spawnrandomenemy function when beginplay starts

	// stuff about the blueprints for the enemy meshes
	UPROPERTY(EditAnywhere, Category = "Spawning")
	TSubclassOf<AEnemyAbstract> slimeBP;

	UPROPERTY(EditAnywhere, Category = "Spawning")
	TSubclassOf<AEnemyAbstract> evilguyBP;

	// array to store all the enemies the factory spawns
	TDoubleLinkedList<AEnemyAbstract*> spawnedenemies;
	// dynamic array
	// called spawnedenemies
	// holds pointers to all the enemies that are spawned

private:
	int32 nextenemyID = 1; // adds to the enemyID variable so it increments

private:
	AEnemyAbstract* selectedenemy = nullptr; // points to selected enemy. starts off nullptr bc you didn't select anything yet

public:
	void selectenemy(int32 enemyID); // enemy selector function
	void killselectedenemy(); // enemy kill function
};
