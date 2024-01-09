#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseWeaponInterface.h"
#include "RifleAR4.generated.h"

class USkeletalMeshComponent;
class USkeletalMesh;
class UParticleSystem;
class UTexture2D;
class USoundAttenuation;

UCLASS()
class FP_TP_API ARifleAR4 : public AActor, public IBaseWeaponInterface{
	public:
		ARifleAR4();
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
		virtual FORCEINLINE const char* GetWeaponName() override { return "AR4"; }
		virtual FORCEINLINE FVector GetWeaponInFPLocation() override { return FVector(30.189329, -14.91, -162.600009); }
		virtual FORCEINLINE FRotator GetWeaponInFPRotation() override { return FRotator(0.0f, -89.999992, -2.000000); }
		virtual FORCEINLINE UTexture2D* GetWeaponTexture() override { return weaponTexture; }
		virtual UTexture2D* GetWeaponFireModeTexture(EWeaponFireModes CurrentWeaponFireMode) override;
		virtual USoundAttenuation* GetWeaponFireSoundAttenuation() override;
		virtual USoundBase* GetWeaponFireSound() override;
		virtual UAnimMontage* GetWeaponInFPFireAnimation() override;
		virtual UAnimMontage* GetWeaponInFPReloadAnimation() override;
		virtual UAnimMontage* GetWeaponInTPReloadAnimation() override;
		virtual UAnimMontage* GetWeaponInTPFireAnimation() override;

	private:
		GENERATED_BODY()
		virtual void BeginPlay() override;
		virtual void Tick(float DeltaTime) override;
		
		UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Soldier, meta = (AllowPrivateAccess = "true"))
		USkeletalMeshComponent* weaponMesh;

		USkeletalMesh *meshObject;
		UParticleSystem *MuzzleParticle;
		UTexture2D *weaponTexture;
		EWeaponFireModes FireMode;
		short bulletShot = 25;
		short remainBullet;
		short bulletInMag = 25;
		short totalBullet = 20;
};