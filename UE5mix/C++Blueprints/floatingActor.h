// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "floatingActor.generated.h"

UCLASS()
class DEVFLOW_API AfloatingActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AfloatingActor();

	// Define Static Mesh Component
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* FloatMesh;

	//Define Speed of float
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "FloatingActor")
	float FloatSpeed = 20.0f;

	//Define Rotation Speed
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "FloatingActor")
	float RotationSpeed = 20.0f;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
