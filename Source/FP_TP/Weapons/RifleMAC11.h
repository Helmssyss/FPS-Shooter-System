// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseWeaponInterface.h"
#include "RifleMAC11.generated.h"

class USkeletalMeshComponent;
class USkeletalMesh;
class UParticleSystem;
class USoundAttenuation;
class USoundBase;
class UStaticMeshComponent;

UCLASS()
class FP_TP_API ARifleMAC11 : public AActor{
	public:	
		ARifleMAC11();
		//virtual FORCEINLINE USkeletalMeshComponent* GetWeaponMesh() override { return weaponMesh; }
		//virtual FORCEINLINE USkeletalMesh* GetWeaponMeshObject() override { return meshObject; }
		//virtual FORCEINLINE UParticleSystem* GetWeaponMuzzleParticle() override { return MuzzleParticle; }
		//virtual FORCEINLINE EWeaponFireModes GetCurrentWeaponFireMode() override { return FireMode; }
		//virtual FORCEINLINE void SetCurrentWeaponFireMode(EWeaponFireModes CurrentWeaponFireMode) override { FireMode = CurrentWeaponFireMode; }
		//virtual UClass* GetWeaponBulletClass() override { return this->StaticClass(); }
		//virtual void WeaponSpreadSize(FVector& Trace, bool bSoldierAimDownSight) override;
		//virtual FORCEINLINE short GetCurrentAmmo() override { return bulletShot; }
		//virtual FORCEINLINE short GetTotalAmmo() override { return totalBullet; }
		//virtual FORCEINLINE void SetCurrentAmmo(uint8 BulletShot) override { bulletShot = BulletShot; }
		//virtual void ReloadWeapon() override;
		//virtual const char* GetWeaponName() override { return "MAC-11"; }
		//virtual FORCEINLINE FVector GetWeaponInFPLocation() override  { return FVector(); }
		//virtual FORCEINLINE FRotator GetWeaponInFPRotation() override { return FRotator(); }
		//virtual FORCEINLINE UTexture2D* GetWeaponTexture() override { return weaponTexture; }
		//virtual UTexture2D* GetWeaponFireModeTexture(EWeaponFireModes CurrentWeaponFireMode) override;
		//virtual USoundAttenuation* GetWeaponFireSoundAttenuation() override;
		//virtual USoundBase* GetWeaponFireSound() override;
		//virtual UAnimMontage* GetWeaponInFPFireAnimation() override;
		//virtual UAnimMontage* GetWeaponInFPReloadAnimation() override;
		//virtual UAnimMontage* GetWeaponInTPReloadAnimation() override;
		//virtual UAnimMontage* GetWeaponInTPFireAnimMontage() override;
		//virtual FORCEINLINE const char* GetWeaponMagazineBoneName() override { return ""; }
		//virtual UClass* GetWeaponMagazineClassUClass() override;
		//virtual UStaticMeshComponent* GetWeaponMagazineMesh() override;

	private:
		GENERATED_BODY()
		virtual void Tick(float DeltaTime) override;
		virtual void BeginPlay() override;

		UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Soldier, meta = (AllowPrivateAccess = "true"))
		USkeletalMeshComponent* weaponMesh;

		USkeletalMesh* meshObject;
		UParticleSystem* MuzzleParticle;
		UTexture2D* weaponTexture;
		EWeaponFireModes FireMode;

		short bulletShot = 25;
		short remainBullet;
		short bulletInMag = 25;
		short totalBullet = 20;
};
