#include "PistolDeagle.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/WidgetComponent.h"
#include "Particles/ParticleSystem.h"
#include "UObject/ConstructorHelpers.h"
#include "Magazine_PistolDeagle.h"
#include "../Bullets/EjectBullet.h"
#include "../Bullets/Bullet9.h"

#define printf(color,format,...) GEngine->AddOnScreenDebugMessage(-1, 2, color, FString::Printf(TEXT(format), ##__VA_ARGS__));

APistolDeagle::APistolDeagle(){
	PrimaryActorTick.bCanEverTick = false;
	const static ConstructorHelpers::FObjectFinder<USkeletalMesh> WeaponMesh(TEXT("/Game/Weapons/Meshes/Pistol/Pistols_A"));
	const static ConstructorHelpers::FObjectFinder<UParticleSystem> WeaponMuzzle(TEXT("/Game/Weapons/FX/P_Pistol_MuzzleFlash_01"));
	const static ConstructorHelpers::FObjectFinder<UTexture2D> WeaponTexture(TEXT("/Game/PistolDeagle"));
	const static ConstructorHelpers::FClassFinder<UUserWidget> GetWeaponCustomizeWidget(TEXT("/Game/Widgets/BP_WeaponCustomizationWidget"));
	widgetClass = GetWeaponCustomizeWidget.Class;

	weaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("PistolDeagle_Mesh"));
	weaponMesh->SetupAttachment(GetRootComponent());
	weaponMesh->SetSkeletalMesh(WeaponMesh.Object);

	widgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("widgetComponent"));
	widgetComponent->SetupAttachment(weaponMesh);
	widgetComponent->SetWidgetClass(widgetClass);
	widgetComponent->SetWidgetSpace(EWidgetSpace::Screen);
	widgetComponent->SetRelativeLocation(FVector(3.984676, 12.445572, 7.446973));
	widgetComponent->SetRelativeScale3D(FVector(0.044720, 0.044720, 0.044720));
	widgetComponent->SetVisibility(false);

	sightMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PistolDeagle_SightMesh"));
	sightMesh->SetupAttachment(weaponMesh, FName("Sight"));
	sightMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	muzzleMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PistolDeagle_MuzzleMesh"));
	muzzleMesh->SetupAttachment(weaponMesh, FName("Muzzle"));
	muzzleMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	gripMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PistolDeagle_GripMesh"));
	gripMesh->SetupAttachment(weaponMesh, FName("Grip"));
	gripMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	meshObject = WeaponMesh.Object;
	MuzzleParticle = WeaponMuzzle.Object;
	weaponTexture = WeaponTexture.Object;

	cosmetics.CosmeticComponents.Add(sightMesh);
	cosmetics.CosmeticComponents.Add(muzzleMesh);
	//cosmetics.CosmeticComponents.Add(gripMesh);
}

void APistolDeagle::SetWeaponCosmetics(FWeaponCosmetics weaponCosmetics){
	cosmetics = weaponCosmetics;
	sightMesh->SetStaticMesh(cosmetics.SightMesh);
	muzzleMesh->SetStaticMesh(cosmetics.MuzzleMesh);
}

void APistolDeagle::BeginPlay() { Super::BeginPlay(); }

void APistolDeagle::Tick(float DeltaTime) { Super::Tick(DeltaTime); }

UClass* APistolDeagle::GetWeaponBulletClass() { return ABullet9::StaticClass(); }
UClass* APistolDeagle::GetWeaponMagazineClass() { return AMagazine_PistolDeagle::StaticClass(); }

void APistolDeagle::WeaponSpreadSize(FVector& Trace, bool bSoldierAimDownSight) {
	if (!bSoldierAimDownSight) {
		Trace.Y += Trace.Y * FMath::RandRange(0.20f, -0.20f);
		Trace.Z += Trace.Z * FMath::RandRange(0.20f, -0.20f);
	}
	else {
		Trace.Y += Trace.Y * FMath::RandRange(0.0f, 0.01f);
		Trace.Z += Trace.Z * FMath::RandRange(0.0f, 0.01f);
	}
}

void APistolDeagle::ReloadWeapon() {
	if (bulletShot < bulletInMag) {
		const short missingBullet = bulletInMag - bulletShot;
		const short willAddBullet = FMath::Min<short>(missingBullet, totalBullet);

		bulletShot += willAddBullet;
		totalBullet -= willAddBullet;
		remainBullet = bulletShot;
	}
}

FVector APistolDeagle::GetWeaponInFPLocation(EWeaponSightType SightType) {
	switch (SightType) {
		case EWeaponSightType::IRON_SIGHT:
			sightType = SightType;
			return FVector(12, 10.72, -168.912973);

		case EWeaponSightType::RED_DOT:
			sightType = SightType;
			return FVector(12, 10.8, -170.812973);

		default:
			return FVector::ZeroVector;
	}

}

UTexture2D* APistolDeagle::GetWeaponFireModeTexture(EWeaponFireModes CurrentWeaponFireMode) {
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

USoundAttenuation* APistolDeagle::GetWeaponFireSoundAttenuation() {
	return LoadObject<USoundAttenuation>(nullptr, TEXT("/Game/Weapons/FX/Sounds/Attenuation/WeaponShot_att"));
}

USoundBase* APistolDeagle::GetWeaponFireSound(EWeaponMuzzleType MuzzleType) {
	switch (MuzzleType) {
	case EWeaponMuzzleType::SUPPRESSOR:
		return LoadObject<USoundBase>(nullptr, TEXT("/Game/Weapons/FX/Sounds/Pistol_Fire_Suppressor_Sound"));

	case EWeaponMuzzleType::NORMAL:
		return LoadObject<USoundBase>(nullptr, TEXT("/Game/Weapons/FX/Sounds/Pistol/Cues/PistolA_Fire_Cue"));

	default:
		return nullptr;
	}
}

UAnimMontage* APistolDeagle::GetWeaponInFPFireAnimation() {
	return LoadObject<UAnimMontage>(nullptr, TEXT("/Game/Character/FirstPerson/Animation/AnimSequance/FP_Pistol_Fire"));;
}

UAnimMontage* APistolDeagle::GetWeaponInFPReloadAnimation() {
	return LoadObject<UAnimMontage>(nullptr, TEXT("/Game/Character/FirstPerson/Animation/FP_A_PistolReload_Deagle"));
}

UAnimMontage* APistolDeagle::GetWeaponInTPReloadAnimation(void) {
	return  LoadObject<UAnimMontage>(nullptr, TEXT("/Game/Character/ThirdPerson/Animation/TP_PistolReload"));
}

UAnimMontage* APistolDeagle::GetWeaponInTPFireAnimMontage(void) {
	return  LoadObject<UAnimMontage>(nullptr, TEXT("/Game/Character/ThirdPerson/Animation/TP_RifleFire"));
}

UAnimationAsset* APistolDeagle::GetWeaponFireAnimation(){
	return LoadObject<UAnimationAsset>(nullptr, TEXT("/Game/Weapons/Animation/PistolDeagle_Fire"));
}

void APistolDeagle::SpawnEjectBullet() {
	FActorSpawnParameters params;
	params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	const FTransform makeTransform = FTransform(GetWeaponMesh()->GetSocketRotation("ejectBullet"), GetWeaponMesh()->GetSocketLocation("ejectBullet"), FVector(1, 1, 1));
	AEjectBullet* EjectSpawnBullet = GetWorld()->SpawnActor<AEjectBullet>(AEjectBullet::StaticClass(), makeTransform, params);
	if (EjectSpawnBullet) {
		EjectSpawnBullet->SetEjectBulletMesh(GetEjectBulletType());
		EjectSpawnBullet->SetLifeSpan(3);
	}
}

void APistolDeagle::PlayWeaponFireAnimation() {
	weaponMesh->PlayAnimation(LoadObject<UAnimationAsset>(nullptr, TEXT("/Game/Weapons/Animation/PistolDeagle_Fire")), false);
}

void APistolDeagle::PlayWeaponShellSetupAnimation() {
	weaponMesh->PlayAnimation(LoadObject<UAnimationAsset>(nullptr, TEXT("/Game/Weapons/Animation/PistolEagle_Reload")), false);
}