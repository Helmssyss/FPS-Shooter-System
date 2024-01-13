#include "RifleAK.h"
#include "Magazine_AK47.h"
#include "../Bullets/EjectBullet.h"
#include "../Bullets/Bullet762.h"

#include "Components/SkeletalMeshComponent.h"
#include "Particles/ParticleSystem.h"
#include "UObject/ConstructorHelpers.h"

#define printf(color,format,...) GEngine->AddOnScreenDebugMessage(-1, 2, color, FString::Printf(TEXT(format), ##__VA_ARGS__));

ARifleAK::ARifleAK() {
	PrimaryActorTick.bCanEverTick = false;
	const static ConstructorHelpers::FObjectFinder<USkeletalMesh> WeaponMesh(TEXT("/Game/Weapons/Meshes/Ka47/SK_KA47"));
	const static ConstructorHelpers::FObjectFinder<UParticleSystem> WeaponMuzzle(TEXT("/Game/Weapons/FX/P_AssaultRifle_MuzzleFlash"));
	const static ConstructorHelpers::FObjectFinder<UTexture2D> WeaponTexture(TEXT("/Game/AK47"));

	weaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("AK47_Mesh"));
	weaponMesh->SetupAttachment(GetRootComponent());
	weaponMesh->SetSkeletalMesh(WeaponMesh.Object);

	meshObject = WeaponMesh.Object;
	MuzzleParticle = WeaponMuzzle.Object;
	weaponTexture = WeaponTexture.Object;
}

void ARifleAK::BeginPlay() {
	Super::BeginPlay();
}

void ARifleAK::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
}

UClass* ARifleAK::GetWeaponBulletClass() {
	return ABullet762::StaticClass();
}

void ARifleAK::WeaponSpreadSize(FVector& Trace, bool bSoldierAimDownSight) {
	if (!bSoldierAimDownSight) {
		Trace.Y += Trace.Y * FMath::RandRange(0.20f, -0.20f);
		Trace.Z += Trace.Z * FMath::RandRange(0.20f, -0.50f);
	}
	else {
		Trace.Y += Trace.Y * FMath::RandRange(0.0f, 0.01f);
		Trace.Z += Trace.Z * FMath::RandRange(0.0f, 0.01f);
	}
}

void ARifleAK::ReloadWeapon() {
	if (bulletShot < bulletInMag) {
		const short missingBullet = bulletInMag - bulletShot;
		const short eklenecekMermi = FMath::Min<short>(missingBullet, totalBullet);

		bulletShot += eklenecekMermi;
		totalBullet -= eklenecekMermi;
		remainBullet = bulletShot;
	}
}

UTexture2D* ARifleAK::GetWeaponFireModeTexture(EWeaponFireModes CurrentWeaponFireMode) {
	switch (CurrentWeaponFireMode) {
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

USoundAttenuation* ARifleAK::GetWeaponFireSoundAttenuation() {
	return LoadObject<USoundAttenuation>(nullptr, TEXT("/Game/Weapons/FX/Sounds/Attenuation/WeaponShot_att"));
}

USoundBase* ARifleAK::GetWeaponFireSound() {
	return LoadObject<USoundBase>(nullptr, TEXT("/Game/Weapons/FX/Sounds/Rifle/Cues/RifleA_Fire_Cue"));
}

UAnimMontage* ARifleAK::GetWeaponInFPFireAnimation() {
	return LoadObject<UAnimMontage>(nullptr, TEXT("/Game/Character/FirstPerson/Animation/FP_RifleFire"));;
}

UAnimMontage* ARifleAK::GetWeaponInFPReloadAnimation(void) {
	return LoadObject<UAnimMontage>(nullptr, TEXT("/Game/Character/FirstPerson/Animation/FP_RifleReload_AK47"));
}

UAnimMontage* ARifleAK::GetWeaponInTPReloadAnimation(void) {
	return  LoadObject<UAnimMontage>(nullptr, TEXT("/Game/Character/ThirdPerson/Animation/TP_RifleReload"));
}

UAnimMontage* ARifleAK::GetWeaponInTPFireAnimation(void) {
	return  LoadObject<UAnimMontage>(nullptr, TEXT("/Game/Character/ThirdPerson/Animation/TP_RifleFire"));
}

UClass* ARifleAK::GetWeaponMagazine() {
	UClass* magazine = AMagazine_AK47::StaticClass();
	return magazine;
}

void ARifleAK::SpawnEjectBullet() {
	FActorSpawnParameters params;
	params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	const FTransform makeTransform = FTransform(GetWeaponMesh()->GetSocketRotation("ejectBullet"), GetWeaponMesh()->GetSocketLocation("ejectBullet"), FVector(1, 1, 1));
	AEjectBullet* EjectSpawnBullet = GetWorld()->SpawnActor<AEjectBullet>(AEjectBullet::StaticClass(), makeTransform, params);
	if (EjectSpawnBullet) {
		printf(FColor::Cyan, "AK EJECT");
		EjectSpawnBullet->SetEjectBulletMesh(GetEjectBulletType());
		EjectSpawnBullet->SetLifeSpan(3);
	}
}

void ARifleAK::PlayWeaponFireAnimation() {
	weaponMesh->PlayAnimation(LoadObject<UAnimationAsset>(nullptr, TEXT("/Game/Weapons/Animation/AK47_Fire")), false);
}

void ARifleAK::PlayWeaponShellSetupAnimation(){
	weaponMesh->PlayAnimation(LoadObject<UAnimationAsset>(nullptr, TEXT("/Game/Weapons/Animation/AK47_SetupShell")), false);
}
