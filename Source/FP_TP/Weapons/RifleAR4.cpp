#include "RifleAR4.h"

#include "Components/SkeletalMeshComponent.h"
#include "../Bullets/Bullet556.h"
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
		Trace.Y += Trace.Y * FMath::RandRange(0.20f, -0.10f);
		Trace.Z += Trace.Z * FMath::RandRange(-0.20f, 0.20f);
	}else {
		Trace.Y += Trace.Y * FMath::RandRange(0.0f, 0.01f);
		Trace.Z += Trace.Z * FMath::RandRange(0.0f, 0.01f);
	}
}

void ARifleAR4::ReloadWeapon(){
	if (bulletShot < bulletInMag) {
		const short missingBullet = bulletInMag - bulletShot;
		const short eklenecekMermi = FMath::Min<short>(missingBullet, totalBullet);

		bulletShot += eklenecekMermi;
		totalBullet -= eklenecekMermi;
		remainBullet = bulletShot;
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

USoundBase* ARifleAR4::GetWeaponFireSound(){
	return LoadObject<USoundBase>(nullptr, TEXT("/Game/Weapons/FX/Sounds/Rifle/Cues/RifleA_Fire_Cue"));
}

UAnimMontage* ARifleAR4::GetWeaponInFPFireAnimation(){
	return LoadObject<UAnimMontage>(nullptr, TEXT("/Game/Character/FirstPerson/Animation/FP_RifleFire"));;
}

UAnimMontage* ARifleAR4::GetWeaponInFPReloadAnimation(void){
	return LoadObject<UAnimMontage>(nullptr, TEXT("/Game/Character/FirstPerson/Animation/FP_RifleReload"));
}

UAnimMontage* ARifleAR4::GetWeaponInTPReloadAnimation(void){
	return  LoadObject<UAnimMontage>(nullptr, TEXT("/Game/Character/ThirdPerson/Animation/TP_RifleReload"));
}

UAnimMontage* ARifleAR4::GetWeaponInTPFireAnimation(void){
	return  LoadObject<UAnimMontage>(nullptr, TEXT("/Game/Character/ThirdPerson/Animation/TP_RifleFire"));
}
