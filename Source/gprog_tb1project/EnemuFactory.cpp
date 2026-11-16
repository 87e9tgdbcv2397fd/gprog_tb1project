// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemuFactory.h"
#include "Enemy_Slime.h"
#include "Enemy_EvilGuy.h"
#include "gprog_tb1projectCharacter.h"
#include "Kismet/GameplayStatics.h"

// now i have to specify what the spawnrandomenemy function is going to do
void AEnemuFactory::spawnrandomenemy() {

	// get a pointer to the player character
	Agprog_tb1projectCharacter* PlayerCharacter = // the pointer is stored in the variable PlayerCharacter
		Cast<Agprog_tb1projectCharacter>(
			UGameplayStatics::GetPlayerCharacter(this, 0) // this stuff makes the pointer of the first player character in the game (me)
		);

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

	// step 5: put the pointer into the linked list, and subscribe it to the player's event broadcasting
	if (newenemy != nullptr) { // only if newenemy doesn't equal nullptr! because if it does, that means it's empty
		// give it the unique enemyID by calling setenemyID function and passing in nextenemyID's value
		newenemy->setenemyID(nextenemyID);

		// increment nextenemyID by 1, ready for the next enemy
		nextenemyID = nextenemyID + 1;

		// adding the pointer to the enemy into the linked list
		spawnedenemies.AddTail(newenemy);

		// subscribe it to the player's event broadcasting
		if (PlayerCharacter != nullptr) {
			newenemy->Subscribe(PlayerCharacter);
		}
	}
}

void AEnemuFactory::selectenemy(int32 enemyID)
{
	// WARNING!!!! for loop that is super complicated looking so i have to put tons of comments to remember what they do

	// first, the conditions for the for loop
	// 1) before the for loop, make a pointer called "Node" and make it point to the head (the first node of the linked list)
	// 2) when "Node" is not nullptr (aka it points to something), run the code block
	// 3) when the code block has been executed, move the pointer "Node" to the next node with Getnextnode

	// now, the stuff inside the code block
	// 1) since the linked list nodes store pointers to the enemies, and not the actual enemies
	// 2) make another pointer, called Enemy, and make it point to the value of the node (which is the enemy pointer)
	// 3) basically, get the pointer inside the node

	// then, compare the node's pointer to enemyID (the input of this function) to see if it's the correct one
	// 1) if block: if the node's enemy matches the value of enemyID, then assign the pointer "selectedenemy" to the value of "Enemy"
	// 2) if it doesn't match, then don't do that, and repeat the process 
	// 3) if it works, also prints in the output log 
	// 4) "return" makes it so the if loop stops immediately after it's found successfully (no need to keep running if it's found)

	for (auto* Node = spawnedenemies.GetHead(); Node != nullptr; Node = Node->GetNextNode())
	{
		AEnemyAbstract* Enemy = Node->GetValue();

		if (Enemy->getenemyID() == enemyID)
		{
			selectedenemy = Enemy;

			UE_LOG(LogTemp, Warning, TEXT("selected enemy: %d"), enemyID);

			return;
		}
	}

	UE_LOG(LogTemp, Warning, TEXT("enemy %d not found"), enemyID); // this only happens if the entire thing runs and no matches are found
}

void AEnemuFactory::killselectedenemy()
{
	if (selectedenemy != nullptr) // only runs if selectedenemy isn't null (aka something is selected)
	{
		for (auto* Node = spawnedenemies.GetHead(); Node != nullptr; Node = Node->GetNextNode()) // run through the linked list
		{
			if (Node->GetValue() == selectedenemy) // if the node matches the selected enemy (aka we found the selected one)
			{
				int32 killedenemyID = selectedenemy->getenemyID(); // variable killedenemy now holds the value/id of selectedenemy (which is about to die)
				
				spawnedenemies.RemoveNode(Node); // detach the node holding said enemy from the linked list

				selectedenemy->Destroy(); // unreal's destroy function to remove the enemy from the scene

				selectedenemy = nullptr; // make the selectedenemy pointer not point to anything anymore, bc it's dead already

				UE_LOG(LogTemp, Warning, TEXT("enemy %d was killed"), killedenemyID); // print to output log

				return; // stop the function when this is done (don't continue going through the list afterwards)
			}
		}
	}
}

void AEnemuFactory::BeginPlay()
{
	Super::BeginPlay();
	
	// when beginplay happens, run spawnrandomenemy function 5 times. this will spawn 5 enemies
	for (int32 i = 0; i < 5; i = i + 1) {
		spawnrandomenemy();
	}
}

