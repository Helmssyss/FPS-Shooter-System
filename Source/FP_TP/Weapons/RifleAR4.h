#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseWeaponInterface.h"
#include "../Bullets/BulletsEnum.h"
#include "RifleAR4.generated.h"

class USkeletalMeshComponent;
class USkeletalMesh;
class UParticleSystem;
class UTexture2D;
class USoundAttenuation;
class UStaticMeshComponent;
class UWidgetComponent;
class AMagazine_AR4;
class IBaseMagazineInterface;

struct FWeaponCosmetics;

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
		virtual FORCEINLINE void SetCurrentAmmo(uint8 BulletShot) override { bulletShot = BulletShot; }
		virtual void ReloadWeapon() override;
		virtual FORCEINLINE const char* GetWeaponName() override { return "AR4"; }
		virtual FVector GetWeaponInFPLocation(EWeaponSightType SightType) override;
		virtual FORCEINLINE FRotator GetWeaponInFPRotation() override { return FRotator(0.0f, -89.999992, -2.000000); }
		virtual FORCEINLINE UTexture2D* GetWeaponTexture() override { return weaponTexture; }
		virtual UTexture2D* GetWeaponFireModeTexture(EWeaponFireModes CurrentWeaponFireMode) override;
		virtual USoundAttenuation* GetWeaponFireSoundAttenuation() override;
		virtual USoundBase* GetWeaponFireSound(EWeaponMuzzleType MuzzleType) override;
		virtual UAnimMontage* GetWeaponInFPFireAnimation() override;
		virtual UAnimMontage* GetWeaponInFPReloadAnimation() override;
		virtual UAnimMontage* GetWeaponInTPReloadAnimation() override;
		virtual UAnimMontage* GetWeaponInTPFireAnimMontage() override;
		virtual UAnimationAsset* GetWeaponFireAnimation() override;
		virtual FORCEINLINE const char* GetWeaponMagazineBoneName() override { return "b_gun_mag"; }
		virtual UClass* GetWeaponMagazineClass() override;
		virtual FORCEINLINE EBulletsEjectType GetEjectBulletType() override { return EBulletsEjectType::EJECT_556; }
		virtual void SpawnEjectBullet() override;
		virtual void PlayWeaponFireAnimation() override;
		virtual FORCEINLINE void PlayWeaponShellSetupAnimation() override {}
		virtual void SetWeaponCosmetics(FWeaponCosmetics weaponCosmetics) override;
		virtual FORCEINLINE FWeaponCosmetics GetWeaponCosmetics() override { return cosmetics; };
		virtual FORCEINLINE UWidgetComponent* GetWeaponCosmeticWidget() override { return widgetComponent; }

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

		UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Soldier, meta = (AllowPrivateAccess = "true"))
		UWidgetComponent* widgetComponent;

		USkeletalMesh *meshObject;
		UParticleSystem *MuzzleParticle;
		UTexture2D *weaponTexture;
		EWeaponFireModes FireMode;
		EWeaponSightType sightType;
		EWeaponMuzzleType muzzleType;
		FWeaponCosmetics cosmetics;

		short bulletShot = 35;
		short bulletInMag = 35;
		short totalBullet = 120;
		short remainBullet;

		TSubclassOf<class UUserWidget> widgetClass;
};