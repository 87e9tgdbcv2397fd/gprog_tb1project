// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/StaticMeshComponent.h" // for the static meshes
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EnemyAbstract.generated.h"

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

public:
	UPROPERTY(VisibleAnywhere, Category = "Enemy") // for the static meshes. both children will inherit this
	UStaticMeshComponent* EnemyMesh;
};
