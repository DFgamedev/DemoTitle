// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectileDemo.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AProjectileDemo::AProjectileDemo()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	// Initialize Projectile Mesh
	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ProjectileMesh"));
	RootComponent = ProjectileMesh;

	//Initialized the Projectile Movement Component
	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
	ProjectileMovementComponent-> InitialSpeed = 3000.0f;
	ProjectileMovementComponent-> MaxSpeed = 3000.0f;
	ProjectileMovementComponent-> bRotationFollowsVelocity = true;
	ProjectileMovementComponent-> bShouldBounce = true;

	Damage = 5;
	
}

// Called when the game starts or when spawned
void AProjectileDemo::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AProjectileDemo::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AProjectileDemo::NotifyHit(UPrimitiveComponent* MyComp, AActor* Other, UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit)
{
	Super::NotifyHit(MyComp, Other, OtherComp, bSelfMoved, HitLocation, HitNormal, NormalImpulse, Hit);

	if(Other != nullptr)
	{
		UGameplayStatics::ApplyPointDamage(Other, Damage, GetActorLocation() - Other-> GetActorLocation(), Hit, nullptr, this, nullptr);
	}
}