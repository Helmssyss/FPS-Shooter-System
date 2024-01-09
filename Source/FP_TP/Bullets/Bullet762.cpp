#include "Bullet762.h"

#include "GameFramework/ProjectileMovementComponent.h"

#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "Components/AudioComponent.h"

#include "UObject/ConstructorHelpers.h"

ABullet762::ABullet762(){
	PrimaryActorTick.bCanEverTick = false;
	const static ConstructorHelpers::FObjectFinder<UStaticMesh> BulletMesh(TEXT("/Game/Weapons/Meshes/Ammunition/SM_Shell_762x39"));

	bulletSphere = CreateDefaultSubobject<USphereComponent>(TEXT("7.62_Sphere"));
	bulletSphere->SetupAttachment(GetRootComponent());

	bulletMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("7.62_Mesh"));
	bulletMesh->SetupAttachment(bulletSphere);
	bulletMesh->SetStaticMesh(BulletMesh.Object);
	bulletMesh->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));

	bulletProjectile = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("7.62_Projectile"));
	bulletProjectile->SetUpdatedComponent(GetRootComponent());
	bulletProjectile->InitialSpeed = 10;
	bulletProjectile->MaxSpeed = 10;
	bulletProjectile->bShouldBounce = true;
	bulletProjectile->ProjectileGravityScale = 0.2;

	bulletAudioCurve = CreateDefaultSubobject<UAudioComponent>(TEXT("RifleBulletAudiuCurve"));
	bulletAudioCurve->SetupAttachment(bulletMesh);
}

void ABullet762::BeginPlay(){
	Super::BeginPlay();
}

void ABullet762::Tick(float DeltaTime){
	Super::Tick(DeltaTime);
}

void ABullet762::DestroyBullet() { Destroy(); }