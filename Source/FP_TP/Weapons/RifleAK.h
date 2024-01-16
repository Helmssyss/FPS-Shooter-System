// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseWeaponInterface.h"
#include "../Bullets/BulletsEnum.h"
#include "RifleAK.generated.h"

class USkeletalMeshComponent;
class USkeletalMesh;
class UParticleSystem;
class UTexture2D;
class USoundAttenuation;
class UStaticMeshComponent;
class AMagazine_AR4;

UCLASS()
class FP_TP_API ARifleAK : public AActor, public IBaseWeaponInterface{
	public:	
		ARifleAK();
		virtual FORCEINLINE USkeletalMeshComponent* GetWeaponMesh() override { return weaponMesh; }
		virtual FORCEINLINE USkeletalMesh* GetWeaponMeshObject() override { return meshObject; }
		virtual FORCEINLINE UParticleSystem* GetWeaponMuzzleParticle() override { return MuzzleParticle; }
		virtual FORCEINLINE EWeaponFireModes GetCurrentWeaponFireMode() override { return FireMode; }
		virtual FORCEINLINE void SetCurrentWeaponFireMode(EWeaponFireModes CurrentWeaponFireMode) override { FireMode = CurrentWeaponFireMode; }
		virtual UClass* GetWeaponBulletClass() override;
		virtual void WeaponSpreadSize(FVector& Trace, bool bSoldierAimDownSight) override;
		virtual FORCEINLINE short GetCurrentAmmo() override { return bulletShot; }
		virtual FORCEINLINE short GetTotalAmmo() override { return totalBullet; }
		virtual FORCEINLINE void SetCurrentAmmo(short BulletShot) override { bulletShot = BulletShot; }
		virtual void ReloadWeapon() override;
		virtual FORCEINLINE const char* GetWeaponName() override { return "AK47"; }
		virtual FVector GetWeaponInFPLocation(EWeaponSightType SightType) override;
		virtual FORCEINLINE FRotator GetWeaponInFPRotation() override { return FRotator(0.000000, -89.989899, -1.866617); }
		virtual FORCEINLINE UTexture2D* GetWeaponTexture() override { return weaponTexture; }
		virtual UTexture2D* GetWeaponFireModeTexture(EWeaponFireModes CurrentWeaponFireMode) override;
		virtual USoundAttenuation* GetWeaponFireSoundAttenuation() override;
		virtual USoundBase* GetWeaponFireSound(EWeaponMuzzleType MuzzleType) override;
		virtual UAnimMontage* GetWeaponInFPFireAnimation() override;
		virtual UAnimMontage* GetWeaponInFPReloadAnimation() override;
		virtual UAnimMontage* GetWeaponInTPReloadAnimation() override;
		virtual UAnimMontage* GetWeaponInTPFireAnimation() override;
		virtual FORCEINLINE const char* GetWeaponMagazineBoneName() override { return "b_gun_mag"; }
		virtual UClass* GetWeaponMagazine() override;
		virtual FORCEINLINE EBulletsEjectType GetEjectBulletType() override { return EBulletsEjectType::EJECT_762; }
		virtual void SpawnEjectBullet() override;
		virtual void PlayWeaponFireAnimation() override;
		virtual void PlayWeaponShellSetupAnimation() override;
		virtual FORCEINLINE UStaticMeshComponent* GetWeaponCustomizeSight() override { return sightMesh; }
		virtual FORCEINLINE UStaticMeshComponent* GetWeaponCustomizeGrip() override { return gripMesh; }
		virtual FORCEINLINE UStaticMeshComponent* GetWeaponCustomizeMuzzle() override { return muzzleMesh; }
		virtual FORCEINLINE EWeaponSightType GetWeaponSightType() override { return sightType; }
		virtual FORCEINLINE EWeaponMuzzleType GetWeaponMuzzleType() override { return muzzleType; }
		virtual FORCEINLINE void SetWeaponMuzzleType(EWeaponMuzzleType MuzzleType) override { muzzleType = MuzzleType; }
		virtual FORCEINLINE void SetWeaponSightType(EWeaponSightType SightType) override { sightType = SightType; }

	private:
		GENERATED_BODY()

		virtual void BeginPlay() override;
		virtual void Tick(float DeltaTime) override;

		UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Soldier, meta = (AllowPrivateAccess = "true"))
		USkeletalMeshComponent* weaponMesh;

		UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Soldier, meta = (AllowPrivateAccess = "true"))
		UStaticMeshComponent* sightMesh;
		
		UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Soldier, meta = (AllowPrivateAccess = "true"))
		UStaticMeshComponent* muzzleMesh;
		
		UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Soldier, meta = (AllowPrivateAccess = "true"))
		UStaticMeshComponent* gripMesh;

		USkeletalMesh* meshObject;
		UParticleSystem* MuzzleParticle;
		UTexture2D* weaponTexture;
		EWeaponFireModes FireMode;
		EWeaponSightType sightType;
		EWeaponMuzzleType muzzleType;

		short bulletShot = 52;
		short bulletInMag = 52;
		short totalBullet = 100;
		short remainBullet;
};
