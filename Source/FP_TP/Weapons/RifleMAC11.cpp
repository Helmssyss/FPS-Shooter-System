#include "RifleMAC11.h"

#include "Particles/ParticleSystem.h"
#include "Components/SkeletalMeshComponent.h"

#include "UObject/ConstructorHelpers.h"

ARifleMAC11::ARifleMAC11(){
	PrimaryActorTick.bCanEverTick = false;
	const static ConstructorHelpers::FObjectFinder<USkeletalMesh> WeaponMesh(TEXT("/Game/Weapons/Meshes/SMG11/SK_SMG11_Y"));
	const static ConstructorHelpers::FObjectFinder<UParticleSystem> WeaponMuzzle(TEXT("/Game/Weapons/FX/P_Pistol_MuzzleFlash_01"));

	weaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("MAC11_Mesh"));
	weaponMesh->SetupAttachment(GetRootComponent());
	weaponMesh->SetSkeletalMesh(WeaponMesh.Object);
	meshObject = WeaponMesh.Object;
	MuzzleParticle = WeaponMuzzle.Object;
}

void ARifleMAC11::BeginPlay(){
	Super::BeginPlay();
}

void ARifleMAC11::Tick(float DeltaTime){
	Super::Tick(DeltaTime);
}

void ARifleMAC11::WeaponSpreadSize(FVector& Trace, bool bSoldierAimDownSight) {
	if (!bSoldierAimDownSight) {
	}else {
	}
}

void ARifleMAC11::ReloadWeapon() {
	if (bulletShot < bulletInMag) {
		const short missingBullet = bulletInMag - bulletShot;
		const short eklenecekMermi = FMath::Min<short>(missingBullet, totalBullet);

		bulletShot += eklenecekMermi;
		totalBullet -= eklenecekMermi;
		remainBullet = bulletShot;
	}
}

UTexture2D* ARifleMAC11::GetWeaponFireModeTexture(EWeaponFireModes CurrentWeaponFireMode) {
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

USoundAttenuation* ARifleMAC11::GetWeaponFireSoundAttenuation() {
	return LoadObject<USoundAttenuation>(nullptr, TEXT("/Game/Weapons/FX/Sounds/Attenuation/WeaponShot_att"));
}

USoundBase* ARifleMAC11::GetWeaponFireSound() {
	return LoadObject<USoundBase>(nullptr, TEXT("/Game/Weapons/FX/Sounds/Rifle/Cues/RifleA_Fire_Cue"));
}

UAnimMontage* ARifleMAC11::GetWeaponInFPFireAnimation(){
	return nullptr;
}

UAnimMontage* ARifleMAC11::GetWeaponInFPReloadAnimation(void) {
	return LoadObject<UAnimMontage>(nullptr, TEXT("/Game/Character/FirstPerson/Animation/FP_RifleReload"));
}

UAnimMontage* ARifleMAC11::GetWeaponInTPReloadAnimation(void){
	return nullptr;
}

UAnimMontage* ARifleMAC11::GetWeaponInTPFireAnimation(void){
	return nullptr;
}
