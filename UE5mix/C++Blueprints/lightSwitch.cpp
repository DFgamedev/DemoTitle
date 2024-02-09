// Fill out your copyright notice in the Description page of Project Settings.


#include "lightSwitch.h"

#include "Components/PointLightComponent.h"
#include "Components/SphereComponent.h"

// Sets default values
AlightSwitch::AlightSwitch()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	DesiredIntensity = 5000.0f;

	PointLight1 = CreateDefaultSubobject<UPointLightComponent>(TEXT("PointLight1"));
	PointLight1->Intensity = DesiredIntensity,
	PointLight1->SetVisibility(false);
	RootComponent = PointLight1;

	Sphere1 = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere1"));
	Sphere1->InitSphereRadius(250.0f);
	Sphere1->SetupAttachment(RootComponent);

	Sphere1-> OnComponentBeginOverlap.AddDynamic(this, &AlightSwitch::OnOverlapBegin);
	Sphere1-> OnComponentEndOverlap.AddDynamic(this, &AlightSwitch::OnOverlapEnd);
	
}

// Called when the game starts or when spawned
void AlightSwitch::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AlightSwitch::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AlightSwitch::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(OtherActor && (OtherActor != this) && OtherComp)
	{
		ToggleLight();
	}
}

void AlightSwitch::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if(OtherActor && (OtherActor != this) && OtherComp)
	{
		ToggleLight();
	}
}

void AlightSwitch::ToggleLight()
{
	PointLight1-> ToggleVisibility();
}
