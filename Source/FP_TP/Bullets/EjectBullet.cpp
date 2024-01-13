#include "EjectBullet.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/RotatingMovementComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"

AEjectBullet::AEjectBullet(){
	PrimaryActorTick.bCanEverTick = false;

	EjectMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("EjectBullet"));
	EjectMesh->SetupAttachment(GetRootComponent());
	EjectMesh->SetCollisionProfileName(FName("BlockAllDynamic"));
	EjectMesh->SetGenerateOverlapEvents(true);

	BulletRotatingMovementComponent = CreateDefaultSubobject<URotatingMovementComponent>(TEXT("EjectBulletROT"));
	BulletRotatingMovementComponent->SetUpdatedComponent(GetRootComponent());
	BulletRotatingMovementComponent->RotationRate = FRotator(1000, 0, -1000);

	projectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("EjectBulletProjectileMovement"));
	projectileMovement->SetUpdatedComponent(GetRootComponent());
	projectileMovement->InitialSpeed = 150;
	projectileMovement->MaxSpeed = 150;
	projectileMovement->bShouldBounce = true;
	projectileMovement->Bounciness = 0.8;
	projectileMovement->ProjectileGravityScale = 1.0f;
	projectileMovement->bRotationFollowsVelocity = false;
	projectileMovement->Velocity = FVector(1, 0, -5);

	FCollisionResponseContainer CollisionResponseContainer;
	CollisionResponseContainer.SetResponse(ECollisionChannel::ECC_Visibility, ECollisionResponse::ECR_Block);
	CollisionResponseContainer.SetResponse(ECollisionChannel::ECC_Camera, ECollisionResponse::ECR_Ignore);
	CollisionResponseContainer.SetResponse(ECollisionChannel::ECC_WorldStatic, ECollisionResponse::ECR_Block);
	CollisionResponseContainer.SetResponse(ECollisionChannel::ECC_WorldDynamic, ECollisionResponse::ECR_Block);
	CollisionResponseContainer.SetResponse(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Ignore);
	CollisionResponseContainer.SetResponse(ECollisionChannel::ECC_PhysicsBody, ECollisionResponse::ECR_Ignore);
	CollisionResponseContainer.SetResponse(ECollisionChannel::ECC_Vehicle, ECollisionResponse::ECR_Ignore);
	CollisionResponseContainer.SetResponse(ECollisionChannel::ECC_Destructible, ECollisionResponse::ECR_Block);

	EjectMesh->SetCollisionResponseToChannels(CollisionResponseContainer);
}

void AEjectBullet::BeginPlay(){
	Super::BeginPlay();
	EjectMesh->OnComponentHit.AddDynamic(this, &AEjectBullet::EjectBulletHit);
}

void AEjectBullet::Tick(float DeltaTime){
	Super::Tick(DeltaTime);
}

void AEjectBullet::EjectBulletHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit){
	//if (BulletRotatingMovementComponent->RotationRate == FRotator::ZeroRotator) {
	//	UGameplayStatics::PlaySoundAtLocation(GetWorld(), LoadObject<USoundBase>(nullptr, TEXT("/Game/Weapons/FX/Sounds/Shell")),GetActorLocation());
	//}
	BulletRotatingMovementComponent->RotationRate = FRotator::ZeroRotator;
}

void AEjectBullet::SetEjectBulletMesh(EBulletsEjectType ejectType) {
	switch (ejectType){
		case EBulletsEjectType::EJECT_556:{
			EjectMesh->SetStaticMesh(LoadObject<UStaticMesh>(nullptr,TEXT("/Game/Weapons/Meshes/Ammunition/SM_Shell_556x45_Empty")));
			break;
		}
		case EBulletsEjectType::EJECT_762: {
			EjectMesh->SetStaticMesh(LoadObject<UStaticMesh>(nullptr, TEXT("/Game/Weapons/Meshes/Ammunition/SM_Shell_762x39_Empty")));
			break;
		}
		default:
			break;
	}
}