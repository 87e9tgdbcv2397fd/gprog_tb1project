// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyAbstract.h"
#include "gprog_tb1projectCharacter.h"

// Sets default values
AEnemyAbstract::AEnemyAbstract()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// for the enemy meshes:
	EnemyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("EnemyMesh"));
	RootComponent = EnemyMesh;

}

// Called when the game starts or when spawned
void AEnemyAbstract::BeginPlay()
{
	Super::BeginPlay();

	EnemyDynamicMaterial = EnemyMesh->CreateAndSetMaterialInstanceDynamic(0); // make a dynamic instance of the material for itself

	if (EnemyDynamicMaterial != nullptr) { // do this so it only works if the pointer is pointing to something. or else it might break
		EnemyDynamicMaterial->GetVectorParameterValue(
			FMaterialParameterInfo("TintColor"),
			OriginalColor
		); // basically read tintcolor (its original color), store it, change to new color if needed, then revert back to tintcolor (original) after a while
	}
}

// Called every frame
void AEnemyAbstract::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AEnemyAbstract::HearNoise(FVector NoiseLocation) 
{
	// step 1: calculate the distance between the player coords (from broadcast) and enemy's own coords
	float distance = FVector::Dist(GetActorLocation(), NoiseLocation); // <- into a variable called "distance"

	// step 2: compare "distance" variable to "hearingrange" variable, and react accordingly
	if (distance <= hearingrange) {
		// enemy can hear noise, so call the changecolor function
		ChangeColor();
	}
	else {
		// enemy can't hear noise
	}
}

void AEnemyAbstract::ChangeColor() 
{
	if (EnemyDynamicMaterial != nullptr) // again, only run this block if it's not nullptr, or else something might break
	{
		EnemyDynamicMaterial->SetVectorParameterValue( // change the color of the material...
			FName("TintColor"),
			ReactionColor // ... to reactioncolor (red in this case)
		);

		GetWorldTimerManager().SetTimer( // calling revertcolor function here
			ColorTimerHandle,
			this,
			&AEnemyAbstract::RevertColor,
			5.0f,
			false
		); // basically use the timer handle to time 5 seconds. after 5 seconds, call revertcolor, don't restart timer
	}
}

void AEnemyAbstract::Subscribe(Agprog_tb1projectCharacter* Player)
{
	if (Player != nullptr) // to make sure the pointer actually points to something (to prevent breaking)
	{
		Player->OnPlayerMadeNoise.AddDynamic(this, &AEnemyAbstract::HearNoise); 
		// whenever Player broadcasts its event, "this" enemy will run its HearNoise function
	}
}

void AEnemyAbstract::RevertColor() // basically the reverse of changecolor ^^ change the material color back to originalcolor
{
	if (EnemyDynamicMaterial != nullptr) {
		EnemyDynamicMaterial->SetVectorParameterValue(
			FName("TintColor"),
			OriginalColor
		);
	}
}

void AEnemyAbstract::setenemyID(int32 newID) 
{
	enemyID = newID;
}

int32 AEnemyAbstract::getenemyID() const
{
	return enemyID;
}