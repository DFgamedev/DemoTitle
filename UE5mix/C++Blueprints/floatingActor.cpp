// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "floatingActor.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

// Sets default values
AfloatingActor::AfloatingActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Create Static Mesh Component and Attach to Root
	FloatMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	FloatMesh->SetupAttachment(RootComponent);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("/Game/StarterContent/Shapes/Shape_Cube.Shape_Cube"));

	// If Mesh Asset is found, Attach to root and set location to 0 in x, y,z.
	if(MeshAsset.Succeeded())
		FloatMesh->SetStaticMesh(MeshAsset.Object);
	FloatMesh->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
}

// Called when the game starts or when spawned
void AfloatingActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AfloatingActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//Define Actor Location and Rotation Variables
	FVector NewLocation = GetActorLocation();
	FRotator NewRotation = GetActorRotation();

	//Define RunningTime
	float RunningTime = GetGameTimeSinceCreation();
	//Add Sin Math DeltaHeight
	float DeltaHeight = (FMath::Sin(RunningTime + DeltaTime) -FMath::Sin(RunningTime));

	//Add Delta Height to Z direction * floatSpeed
	NewLocation.Z += DeltaHeight * FloatSpeed;

	//Add Rotation to Yaw * Rotation Speed
	float DeltaRotation = DeltaTime * RotationSpeed;
	NewRotation.Yaw += DeltaRotation;

	// Set Actor Location and Rotation
	SetActorLocationAndRotation(NewLocation, NewRotation);

}
