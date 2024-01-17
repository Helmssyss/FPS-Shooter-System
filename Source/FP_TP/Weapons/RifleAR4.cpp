#include "RifleAR4.h"
#include "../Bullets/Bullet556.h"
#include "Magazine_AR4.h"
#include "../Bullets/EjectBullet.h"

#include "Components/SkeletalMeshComponent.h"
#include "Particles/ParticleSystem.h"
#include "UObject/ConstructorHelpers.h"

#define printf(color,format,...) GEngine->AddOnScreenDebugMessage(-1, 2, color, FString::Printf(TEXT(format), ##__VA_ARGS__));

ARifleAR4::ARifleAR4(){
	PrimaryActorTick.bCanEverTick = false;
	const static ConstructorHelpers::FObjectFinder<USkeletalMesh> WeaponMesh(TEXT("/Game/Weapons/Meshes/AR4/SK_AR4"));
	const static ConstructorHelpers::FObjectFinder<UParticleSystem> WeaponMuzzle(TEXT("/Game/Weapons/FX/P_AssaultRifle_MuzzleFlash"));
	const static ConstructorHelpers::FObjectFinder<UTexture2D> WeaponTexture(TEXT("/Game/AR4"));

	weaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("AR4_Mesh"));
	weaponMesh->SetupAttachment(GetRootComponent());
	weaponMesh->SetSkeletalMesh(WeaponMesh.Object);

	sightMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("AK47_SightMesh"));
	sightMesh->SetupAttachment(weaponMesh, FName("Sight"));
	sightMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	muzzleMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("AK47_MuzzleMesh"));
	muzzleMesh->SetupAttachment(weaponMesh, FName("Muzzle"));
	muzzleMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	gripMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("AK47_GripMesh"));
	gripMesh->SetupAttachment(weaponMesh, FName("Grip"));
	gripMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	meshObject = WeaponMesh.Object;
	MuzzleParticle = WeaponMuzzle.Object;
	weaponTexture = WeaponTexture.Object;
}

void ARifleAR4::BeginPlay(){
	Super::BeginPlay();
}

void ARifleAR4::Tick(float DeltaTime){
	Super::Tick(DeltaTime);
}

UClass* ARifleAR4::GetWeaponBulletClass() {
	return ABullet556::StaticClass();
}

void ARifleAR4::WeaponSpreadSize(FVector &Trace, bool bSoldierAimDownSight){
	if (!bSoldierAimDownSight) {
		Trace.Y += Trace.Y * FMath::RandRange(0.20f, -0.20f);
		Trace.Z += Trace.Z * FMath::RandRange(0.20f, -0.20f);
	}else {
		Trace.Y += Trace.Y * FMath::RandRange(0.0f, 0.01f);
		Trace.Z += Trace.Z * FMath::RandRange(0.0f, 0.01f);
	}
}

void ARifleAR4::ReloadWeapon(){
	if (bulletShot < bulletInMag) {
		const short missingBullet = bulletInMag - bulletShot;
		const short willAddBullet = FMath::Min<short>(missingBullet, totalBullet);

		bulletShot += willAddBullet;
		totalBullet -= willAddBullet;
		remainBullet = bulletShot;
	}
}

FVector ARifleAR4::GetWeaponInFPLocation(EWeaponSightType SightType){
	switch (SightType){
		case EWeaponSightType::IRON_SIGHT:
			return FVector(30.189329, -14.91, -162.600009);
		
		case EWeaponSightType::RED_DOT:
			return FVector(30.189329, -14.91, -162.600009);
		
		default:
			return FVector::ZeroVector;
	}
	
}

UTexture2D* ARifleAR4::GetWeaponFireModeTexture(EWeaponFireModes CurrentWeaponFireMode){
	switch (CurrentWeaponFireMode){
		case EWeaponFireModes::AUTO_MODE:
			return LoadObject<UTexture2D>(nullptr, TEXT("/Game/Auto_bullet"));
		
		case EWeaponFireModes::SEMI_AUTO_MODE:
			return LoadObject<UTexture2D>(nullptr, TEXT("/Game/Semi_Auto_bullet"));

		case EWeaponFireModes::SINGLE_MODE:
			return LoadObject<UTexture2D>(nullptr, TEXT("/Game/Single_bullet"));

		default:
			return nullptr;
	}
}

USoundAttenuation* ARifleAR4::GetWeaponFireSoundAttenuation(){
	return LoadObject<USoundAttenuation>(nullptr, TEXT("/Game/Weapons/FX/Sounds/Attenuation/WeaponShot_att"));
}

USoundBase* ARifleAR4::GetWeaponFireSound(EWeaponMuzzleType MuzzleType){
	switch (MuzzleType){
		case EWeaponMuzzleType::SUPPRESSOR:
			return LoadObject<USoundBase>(nullptr, TEXT("/Game/Weapons/FX/Sounds/AR4_FireSuppressor"));
		
		case EWeaponMuzzleType::NORMAL:
			return LoadObject<USoundBase>(nullptr, TEXT("/Game/Weapons/FX/Sounds/Rifle/Cues/RifleA_Fire_Cue"));
		
		default:
			return nullptr;
	}
}

UAnimMontage* ARifleAR4::GetWeaponInFPFireAnimation(){
	return LoadObject<UAnimMontage>(nullptr, TEXT("/Game/Character/FirstPerson/Animation/FP_RifleFire"));;
}

UAnimMontage* ARifleAR4::GetWeaponInFPReloadAnimation(void){
	return LoadObject<UAnimMontage>(nullptr, TEXT("/Game/Character/FirstPerson/Animation/FP_RifleReload_AR4"));
}

UAnimMontage* ARifleAR4::GetWeaponInTPReloadAnimation(void){
	return  LoadObject<UAnimMontage>(nullptr, TEXT("/Game/Character/ThirdPerson/Animation/TP_RifleReload"));
}

UAnimMontage* ARifleAR4::GetWeaponInTPFireAnimation(void){
	return  LoadObject<UAnimMontage>(nullptr, TEXT("/Game/Character/ThirdPerson/Animation/TP_RifleFire"));
}

UClass* ARifleAR4::GetWeaponMagazine(){
	UClass* magazine = AMagazine_AR4::StaticClass();
	return magazine;
}

void ARifleAR4::SpawnEjectBullet(){
	FActorSpawnParameters params;
	params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	const FTransform makeTransform = FTransform(GetWeaponMesh()->GetSocketRotation("ejectBullet"), GetWeaponMesh()->GetSocketLocation("ejectBullet"), FVector(1, 1, 1));
	AEjectBullet* EjectSpawnBullet = GetWorld()->SpawnActor<AEjectBullet>(AEjectBullet::StaticClass(), makeTransform, params);
	if (EjectSpawnBullet) {
		EjectSpawnBullet->SetEjectBulletMesh(GetEjectBulletType());
		EjectSpawnBullet->SetLifeSpan(3);
	}
}

void ARifleAR4::PlayWeaponFireAnimation(){
	weaponMesh->PlayAnimation(LoadObject<UAnimationAsset>(nullptr,TEXT("/Game/Weapons/Animation/AR4_Fire")), false);
}
