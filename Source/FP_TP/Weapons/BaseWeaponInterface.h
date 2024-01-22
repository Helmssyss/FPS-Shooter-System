#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "WeaponEnums.h"
#include "../Bullets/BulletsEnum.h"
#include "WeaponEnums.h"
#include "BaseWeaponInterface.generated.h"

class UAnimationAsset;
class USkeletalMeshComponent;
class USkeletalMesh;
class UParticleSystem;
class UTexture2D;
class USoundAttenuation;
class USoundBase;
class UAnimMontage;
class UWidgetComponent;

USTRUCT(BlueprintType)
struct FWeaponCosmetics {
	public:
		GENERATED_BODY()

		UPROPERTY()
		UStaticMesh* SightMesh;
		
		UPROPERTY()
		UStaticMesh* MuzzleMesh;

		UPROPERTY()
		EWeaponMuzzleType MuzzleType;

		UPROPERTY()
		EWeaponSightType SightType;

		UPROPERTY()
		EWeaponFireModes CurrentWeaponFireMode;

		UPROPERTY()
		TArray<UStaticMeshComponent*> CosmeticComponents;
};

UINTERFACE(MinimalAPI)
class UBaseWeaponInterface : public UInterface { GENERATED_BODY() };

class FP_TP_API IBaseWeaponInterface{
	public:
		virtual USkeletalMeshComponent *GetWeaponMesh(void) = 0;
		virtual USkeletalMesh *GetWeaponMeshObject(void) = 0;
		virtual UClass *GetWeaponBulletClass(void) = 0;
		virtual UParticleSystem *GetWeaponMuzzleParticle(void) = 0;
		virtual void SetCurrentWeaponFireMode(EWeaponFireModes CurrentWeaponFireMode) = 0;
		virtual EWeaponFireModes GetCurrentWeaponFireMode(void) = 0;
		virtual void WeaponSpreadSize(FVector& Trace, bool bSoldierAimDownSight) = 0;
		virtual short GetCurrentAmmo(void) = 0;
		virtual short GetTotalAmmo(void) = 0;
		virtual void SetCurrentAmmo(uint8 BulletShot) = 0;
		virtual void ReloadWeapon(void) = 0;
		virtual const char* GetWeaponName(void) = 0;
		virtual UTexture2D* GetWeaponTexture(void) = 0;
		virtual UTexture2D* GetWeaponFireModeTexture(EWeaponFireModes CurrentWeaponFireMode) = 0;
		virtual USoundAttenuation* GetWeaponFireSoundAttenuation(void) = 0;
		virtual USoundBase* GetWeaponFireSound(EWeaponMuzzleType MuzzleType) = 0;
		virtual UAnimMontage* GetWeaponInFPFireAnimation(void) = 0;
		virtual UAnimMontage* GetWeaponInFPReloadAnimation(void) = 0;
		virtual UAnimMontage* GetWeaponInTPReloadAnimation(void) = 0;
		virtual UAnimMontage* GetWeaponInTPFireAnimMontage(void) = 0;
		virtual FVector GetWeaponInFPLocation(EWeaponSightType SightType) = 0;
		virtual FRotator GetWeaponInFPRotation(void) = 0;
		virtual const char* GetWeaponMagazineBoneName(void) = 0;
		virtual UClass* GetWeaponMagazineClass(void) = 0;
		virtual EBulletsEjectType GetEjectBulletType(void) = 0;
		virtual void SpawnEjectBullet(void) = 0;
		virtual void PlayWeaponFireAnimation(void) = 0;
		virtual void PlayWeaponShellSetupAnimation(void) = 0;
		virtual UAnimationAsset* GetWeaponFireAnimation(void) = 0;
		virtual FWeaponCosmetics GetWeaponCosmetics() = 0;
		virtual void SetWeaponCosmetics(FWeaponCosmetics weaponCosmetics) = 0;
		virtual UWidgetComponent* GetWeaponCosmeticWidget(void) = 0;

	private:
		GENERATED_BODY()
};
