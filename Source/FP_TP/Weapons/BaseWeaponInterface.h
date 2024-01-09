#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
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

UINTERFACE(MinimalAPI)
class UBaseWeaponInterface : public UInterface { GENERATED_BODY() };

class FP_TP_API IBaseWeaponInterface{
	public:
		virtual USkeletalMeshComponent* GetWeaponMesh(void) = 0;
		virtual USkeletalMesh* GetWeaponMeshObject(void) = 0;
		virtual UClass *GetWeaponBulletClass(void) = 0;
		virtual UParticleSystem* GetWeaponMuzzleParticle(void) = 0;
		virtual void SetCurrentWeaponFireMode(EWeaponFireModes CurrentWeaponFireMode) = 0;
		virtual EWeaponFireModes GetCurrentWeaponFireMode(void) = 0;
		virtual void WeaponSpreadSize(FVector& Trace, bool bSoldierAimDownSight) = 0;
		virtual short GetCurrentAmmo(void) = 0;
		virtual short GetTotalAmmo(void) = 0;
		virtual void SetCurrentAmmo(short BulletShot) = 0;
		virtual void ReloadWeapon(void) = 0;
		virtual const char* GetWeaponName(void) = 0;
		virtual UTexture2D* GetWeaponTexture(void) = 0;
		virtual UTexture2D* GetWeaponFireModeTexture(EWeaponFireModes CurrentWeaponFireMode) = 0;
		virtual USoundAttenuation* GetWeaponFireSoundAttenuation(void) = 0;
		virtual USoundBase* GetWeaponFireSound(void) = 0;

		// spesific of First Person and Third Person Animations
		virtual UAnimMontage* GetWeaponInFPFireAnimation(void) = 0;
		virtual UAnimMontage* GetWeaponInFPReloadAnimation(void) = 0;
		virtual UAnimMontage* GetWeaponInTPReloadAnimation(void) = 0;
		virtual UAnimMontage* GetWeaponInTPFireAnimation(void) = 0;
		virtual FVector GetWeaponInFPLocation(void) = 0;
		virtual FRotator GetWeaponInFPRotation(void) = 0;

	private:
		GENERATED_BODY()
};
