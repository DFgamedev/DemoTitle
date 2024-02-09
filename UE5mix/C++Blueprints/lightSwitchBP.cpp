// Fill out your copyright notice in the Description page of Project Settings.


#include "lightSwitchBP.h"

#include "Components/PointLightComponent.h"
#include "Components/SphereComponent.h"

// Sets default values
AlightSwitchBP::AlightSwitchBP()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	DesiredIntensity = 5000.0f;

	PointLight1 = CreateDefaultSubobject<UPointLightComponent>(TEXT("PointLight1"));
	PointLight1->Intensity = DesiredIntensity;
	PointLight1->SetVisibility(false);
	RootComponent = PointLight1;

	Sphere1 = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere1"));
	Sphere1->InitSphereRadius(250.0f);
	Sphere1->SetupAttachment(RootComponent);
	Sphere1->SetHiddenInGame(false);

	Sphere1-> OnComponentBeginOverlap.AddDynamic(this, &AlightSwitchBP::OnOverlapBegin);
	Sphere1-> OnComponentEndOverlap.AddDynamic(this, &AlightSwitchBP::OnOverlapEnd);
}

// Called when the game starts or when spawned
void AlightSwitchBP::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AlightSwitchBP::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AlightSwitchBP::OnOverlapBegin_Implementation(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(OtherActor && (OtherActor != this) && OtherComp)
	{
		ToggleLight();
	}
}

void AlightSwitchBP::OnOverlapEnd_Implementation(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if(OtherActor && (OtherActor != this) && OtherComp)
	{
		ToggleLight();
	}
}

void AlightSwitchBP::ToggleLight()
{
	PointLight1->ToggleVisibility();
}