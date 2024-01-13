#include "Bullet556.h"

#include "GameFramework/ProjectileMovementComponent.h"

#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "Components/AudioComponent.h"

#include "PhysicalMaterials/PhysicalMaterial.h"
#include "Particles/ParticleSystemComponent.h"

#include "UObject/ConstructorHelpers.h"
#include "Kismet/GameplayStatics.h"

#define printf(color,format,...) GEngine->AddOnScreenDebugMessage(-1, 3, color, FString::Printf(TEXT(format), ##__VA_ARGS__));

ABullet556::ABullet556() {
	PrimaryActorTick.bCanEverTick = false;
	const static ConstructorHelpers::FObjectFinder<UStaticMesh> BulletMesh(TEXT("/Game/Weapons/Meshes/Ammunition/SM_Shell_556x45"));
	const static ConstructorHelpers::FObjectFinder<UParticleSystem> GetBulletTrail(TEXT("/Game/Weapons/FX/P_AssaultRifle_Tracer_01"));

	bulletSphere = CreateDefaultSubobject<USphereComponent>(TEXT("5.56_Sphere"));
	bulletSphere->SetupAttachment(GetRootComponent());
	bulletSphere->SetSphereRadius(2.0f);
	bulletSphere->SetCollisionProfileName(FName("BlockAllDynamic"));
	bulletSphere->SetGenerateOverlapEvents(true);
	bulletSphere->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	//bulletSphere->SetHiddenInGame(false);

	bulletMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("5.56_Mesh"));
	bulletMesh->SetupAttachment(bulletSphere);
	bulletMesh->SetStaticMesh(BulletMesh.Object);
	bulletMesh->SetCollisionProfileName(FName("BlockAllDynamic"));
	bulletMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics); 
	bulletMesh->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));
	bulletMesh->SetCastShadow(false);

	bulletTrail = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("5.56_Trail"));
	bulletTrail->SetupAttachment(bulletMesh);
	bulletTrail->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));
	bulletTrail->SetRelativeScale3D(FVector(0.39, 0.3, 0.3));
	bulletTrail->SetTemplate(GetBulletTrail.Object);

	bulletProjectile = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("5.56_Projectile"));
	bulletProjectile->SetUpdatedComponent(GetRootComponent());
	bulletProjectile->InitialSpeed = 10500;
	bulletProjectile->MaxSpeed = 10500;
	bulletProjectile->bShouldBounce = true;
	bulletProjectile->ProjectileGravityScale = 0.3f;

	//bulletAudioCurve = CreateDefaultSubobject<UAudioComponent>(TEXT("RifleBulletAudiuCurve"));
	//bulletAudioCurve->SetupAttachment(bulletMesh);
}

void ABullet556::BeginPlay() {
	Super::BeginPlay();
	bulletSphere->OnComponentHit.AddDynamic(this, &ABullet556::BulletHit);
}

void ABullet556::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
}

void ABullet556::BulletHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit){
	BulletImpactParticle(OtherComp, Hit);
	DestroyBullet();
}

void ABullet556::BulletImpactParticle(UPrimitiveComponent* OtherComp, const FHitResult& Hit){
	const FVector ImpactDirection = Hit.ImpactPoint - GetActorLocation();
	FRotator NewRotation = ImpactDirection.Rotation();
	NewRotation.Pitch += 90.0f;
	const FTransform SpawnTransform(NewRotation, Hit.ImpactPoint, FVector(0.5f));
	const UMaterialInterface* MaterialInterface = OtherComp->GetMaterial(0);
	if (MaterialInterface) {
		UParticleSystem* particle = LoadObject<UParticleSystem>(nullptr, TEXT("/Game/Realistic_Starter_VFX_Pack_Vol2/Particles/Hit/P_Concrete"));
		const UPhysicalMaterial* GetPhysicalMaterial = MaterialInterface->GetPhysicalMaterial();
		switch (GetPhysicalMaterial->SurfaceType) {
			case EPhysicalSurface::SurfaceType1:{
				printf(FColor::Red, "SurfaceType1");
				USoundBase* ImpactEmitterSound = LoadObject<USoundBase>(nullptr, TEXT("/Game/Weapons/FX/Sounds/Rifle/Cues/Rifle_ImpactSurface_Cue"));
				USoundAttenuation* ImpactSoundAttenuation = LoadObject<USoundAttenuation>(nullptr, TEXT("/Game/Weapons/FX/Sounds/Attenuation/ProjectileImpact_att"));
				UGameplayStatics::SpawnSoundAtLocation(GetWorld(), ImpactEmitterSound, Hit.ImpactPoint, FRotator::ZeroRotator, 1, 1, 0, ImpactSoundAttenuation);
				UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), particle, SpawnTransform);
				UMaterialInterface *BulletHoleDecalMaterial = Cast<UMaterialInterface>(StaticLoadObject(UMaterialInterface::StaticClass(), nullptr,TEXT("/Game/M_BulletHole_Material")));
				if(BulletHoleDecalMaterial)
					UGameplayStatics::SpawnDecalAttached(BulletHoleDecalMaterial, FVector(10, 10, 10), OtherComp, NAME_None, Hit.Location, FRotationMatrix::MakeFromX(Hit.Normal).Rotator(), EAttachLocation::KeepWorldPosition, 10);
				break;
			}
			
			case EPhysicalSurface::SurfaceType2:
				break;

			case EPhysicalSurface::SurfaceType3:
				//UGameplayStatics::SpawnEmitterAtLocation();
				break;
			default: {
				printf(FColor::Red, "SurfaceType1");
				USoundBase* ImpactEmitterSound = LoadObject<USoundBase>(nullptr, TEXT("/Game/Weapons/FX/Sounds/Rifle/Cues/Rifle_ImpactSurface_Cue"));
				USoundAttenuation* ImpactSoundAttenuation = LoadObject<USoundAttenuation>(nullptr, TEXT("/Game/Weapons/FX/Sounds/Attenuation/ProjectileImpact_att"));
				UGameplayStatics::SpawnSoundAtLocation(GetWorld(), ImpactEmitterSound, Hit.ImpactPoint, FRotator::ZeroRotator, 1, 1, 0, ImpactSoundAttenuation);
				UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), particle, SpawnTransform);
				break;
			}
		}
	}
}

void ABullet556::DestroyBullet() { Destroy(); }