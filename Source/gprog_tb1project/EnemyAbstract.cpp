// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyAbstract.h"

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
	
}

// Called every frame
void AEnemyAbstract::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

