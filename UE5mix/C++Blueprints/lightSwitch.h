// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "lightSwitch.generated.h"

UCLASS()
class DEVFLOW_API AlightSwitch : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AlightSwitch();

	// Add a pointLight Component
	UPROPERTY(VisibleAnywhere, Category= "SwitchComponent")
	class UPointLightComponent* PointLight1;

	// Sphere Collider for Overlaps
	UPROPERTY(VisibleAnywhere, Category= "SwitchComponent")
	class USphereComponent* Sphere1;

	// On Overlap Function
	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	// End Overlap Function
	UFUNCTION()
	void OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	// Function for toggling light
	UFUNCTION()
	void ToggleLight();

	// Define Intensity
	UPROPERTY(VisibleAnywhere, Category= "SwitchVariables")
	float DesiredIntensity;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
