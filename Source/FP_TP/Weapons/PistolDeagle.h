#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseWeaponInterface.h"
#include "../Bullets/BulletsEnum.h"
#include "PistolDeagle.generated.h"

class USkeletalMeshComponent;
class USkeletalMesh;
class UParticleSystem;
class UTexture2D;
class USoundAttenuation;
class UStaticMeshComponent;
class AMagazine_AR4;
class UWidgetComponent;
class IBaseMagazineInterface;

struct FWeaponCosmetics;

UCLASS()
class FP_TP_API APistolDeagle : public AActor, public IBaseWeaponInterface{
	public:	
		APistolDeagle();
		virtual FORCEINLINE USkeletalMeshComponent* GetWeaponMesh() override { return weaponMesh; }
		virtual FORCEINLINE USkeletalMesh* GetWeaponMeshObject() override { return meshObject; }
		virtual FORCEINLINE UParticleSystem* GetWeaponMuzzleParticle() override { return MuzzleParticle; }
		virtual FORCEINLINE EWeaponFireModes GetCurrentWeaponFireMode() override { return FireMode; }
		virtual FORCEINLINE void SetCurrentWeaponFireMode(EWeaponFireModes CurrentWeaponFireMode) override { FireMode = CurrentWeaponFireMode; }
		virtual UClass* GetWeaponBulletClass() override;
		virtual UClass* GetWeaponMagazineClass() override;
		virtual void WeaponSpreadSize(FVector& Trace, bool bSoldierAimDownSight) override;
		virtual FORCEINLINE short GetCurrentAmmo() override { return bulletShot; }
		virtual FORCEINLINE short GetTotalAmmo() override { return totalBullet; }
		virtual FORCEINLINE void SetCurrentAmmo(uint8 BulletShot) override { bulletShot = BulletShot; }
		virtual void ReloadWeapon() override;
		virtual FORCEINLINE const char* GetWeaponName() override { return "AR4"; }
		virtual FVector GetWeaponInFPLocation(EWeaponSightType SightType) override;
		virtual FORCEINLINE FRotator GetWeaponInFPRotation() override { return FRotator(-2.597670, -96.319809, -4.599595); }
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
		virtual FORCEINLINE EBulletsEjectType GetEjectBulletType() override { return EBulletsEjectType::EJECT_9; }
		virtual void SpawnEjectBullet() override;
		virtual void PlayWeaponFireAnimation() override;
		virtual void PlayWeaponShellSetupAnimation() override;

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

		USkeletalMesh* meshObject;
		UParticleSystem* MuzzleParticle;
		UTexture2D* weaponTexture;
		EWeaponFireModes FireMode;
		EWeaponSightType sightType;
		EWeaponMuzzleType muzzleType;

		UPROPERTY()
		FWeaponCosmetics cosmetics;

		short bulletShot = 12;
		short bulletInMag = 12;
		short totalBullet = 40;
		short remainBullet;

		TSubclassOf<class UUserWidget> widgetClass;
};
