// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemuFactory.h"
#include "Enemy_Slime.h"
#include "Enemy_EvilGuy.h"

// now i have to specify what the spawnrandomenemy function is going to do
void AEnemuFactory::spawnrandomenemy() {

	// step 1: pick whether to spawn Slime (0) or EvilGuy(1) and store it into enemychoice
	int32 enemychoice = FMath::RandRange(0, 1);

	// step 2: pick a random spot (in range) to spawn whatever it is
	// starting coords are the enemyfactory coords. change the x/y coords, not the z coord, and store new pos in spawnlocation
	FVector spawnlocation = GetActorLocation() + FVector( // store the random spot picked in the variable spawnlocation
		FMath::RandRange(-SpawnRadius, SpawnRadius), // x coordinate
		FMath::RandRange(-SpawnRadius, SpawnRadius), // y coordinate
		0.0f // z coordinate does not change
	);
	// step 3: make a variable called newenemy to store the pointer that points to the about-to-be-spawned enemy
	AEnemyAbstract* newenemy = nullptr;

	// step 4: actually spawn the thing
	if (enemychoice == 0) { // if number picked was 0,
		newenemy = GetWorld()->SpawnActor<AEnemyAbstract>( // tell unreal to spawn an actor instance of Enemy_Slime, and put into newenemy,
			slimeBP,
			spawnlocation, // at the previously calculated random location,
			FRotator::ZeroRotator // with no rotations
		);
	}
	else { // if number picked was 1 instead,
		newenemy = GetWorld()->SpawnActor<AEnemyAbstract>( // spawn instance of Enemy_EvilGuy, and put into newenemy,
			evilguyBP,
			spawnlocation, // at that location,
			FRotator::ZeroRotator // with no rotation
		);
	}

	// step 5: put the pointer into the array
	if (newenemy != nullptr) { // only if newenemy doesn't equal nullptr! because if it does, that means it's empty
		spawnedenemies.AddTail(newenemy); // adding the pointer to the enemy into the array
	}
}

void AEnemuFactory::BeginPlay()
{
	Super::BeginPlay();
	
	// when beginplay happens, run spawnrandomenemy function 10 times. this will spawn 10 enemies
	for (int32 i = 0; i < 10; i = i + 1) {
		spawnrandomenemy();
	}
}

