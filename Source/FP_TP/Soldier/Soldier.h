#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Components/TimelineComponent.h"
#include "Soldier.generated.h"

class USpringArmComponent;
class UCameraComponent;
class USkeletalMeshComponent;
class UCurveFloat;
class UAnimMontage;
class UCameraShakeBase;
class USoldierInterfaceWidget;
class UWeaponCustomizeWidget;
class ABaseMagazine;
class IBaseWeaponInterface;
class UChildActorComponent;
class USceneComponent;
class UStaticMeshComponent;

UCLASS()
class FP_TP_API ASoldier : public ACharacter{
	public:
		ASoldier();
		FORCEINLINE bool GetAimDownSightState() const { return bAimDownSight; }
		FORCEINLINE USkeletalMeshComponent *GetTPGunMesh() const { return TP_Gun; }
		FORCEINLINE USkeletalMeshComponent *GetFPArm() const { return FP_Arms; }
		FORCEINLINE void SetCurrentFPRightHandWeapon(IBaseWeaponInterface* newWeapon) { currentRightHandWeapon = newWeapon; }
		FORCEINLINE IBaseWeaponInterface *GetCurrentFPRightHandWeapon() const { return currentRightHandWeapon; }
		FORCEINLINE void SetPreviousMagazineOwner(ABaseMagazine *magazine) { currentGetMagazineOwner = magazine; }
		FORCEINLINE ABaseMagazine* GetPreviousMagazineOwner() { return currentGetMagazineOwner; }
		FORCEINLINE void SetReloadState(bool bReloadState) { bReloading = bReloadState; }
		FORCEINLINE bool GetReloadState() { return bReloading; }
		FORCEINLINE float GetMouseX() const { return yawInput; }
		FORCEINLINE float GetMouseY() const { return pitchInput; }
		FORCEINLINE bool GetWeaponCustomizeState() const { return bWeaponCustomize; }
		FORCEINLINE bool GetSprintState() const { return bSprint; }
		FORCEINLINE bool GetSwitchWeaponState() const { return bIsSecondWeapon; }
		FORCEINLINE UChildActorComponent *GetFPPrimaryGun() const { return FP_PrimaryGun; }
		FORCEINLINE UChildActorComponent* GetFPSecondaryGun() const { return FP_SecondaryGun; }
		FORCEINLINE float GetCurrentWeaponClipDistance() const { return clipDistance; }
		FORCEINLINE bool GetCurrentWeaponIsClipping() const { return bWeaponIsClipping; }
		FORCEINLINE UStaticMeshComponent* GetTPGunSightMesh() const { return TP_SightMesh; }
		FORCEINLINE UStaticMeshComponent* GetTPGunMuzzleMesh() const { return TP_MuzzleMesh; }
		void SetSelectWeaponCosmetics();

	private:
		GENERATED_BODY()
		
		virtual void BeginPlay() override;
		virtual void Tick(float DeltaTime) override;
		virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
		void MoveFB(float Value);
		void MoveRL(float Value);
		void TurnRL(float Rate);
		void LookUp(float Rate);
		void Sprint();
		void SprintStop();
		void ShootFire();
		void FireMode();
		void OnFire();
		void OnFireReleased();
		void SetSemiAutoFire();
		void Reload();
		void AimDownSightStart();
		void AimDownSightReverse();
		void RecoilStart();
		void RecoilReverse();
		void RecoilInterpolate(float DeltaTime);
		void WeaponCosmeticAnimation();
		void FirstWeapon();
		void SecondWeapon();
		FORCEINLINE FVector SelectVector(const FVector &A, const FVector &B, const bool &bSelectA) const { return bSelectA ? A : B; }
		FORCEINLINE FRotator FindLookAtRotation(const FVector &Start, const FVector &Target) const { return FRotationMatrix::MakeFromX(Target - Start).Rotator(); }
		FORCEINLINE FRotator DeltaRotator(const FRotator& A, const FRotator& B) const { return (A - B).GetNormalized(); }
		
		UFUNCTION()
		void AimDownSightUpdate(float Alpha);
		
		UFUNCTION()
		void OnAimDownSightFinished();

		UFUNCTION()
		void SoldierInterfaceWidgetSetHide();

		UFUNCTION()
		void RecoilStartPitch(float Alpha);

		UFUNCTION()
		void RecoilStartYaw(float Alpha);

		UFUNCTION()
		void WeaponClipping();

		UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		USpringArmComponent *FP_CameraBoom;

		UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		UCameraComponent *FP_Camera;

		UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Soldier, meta = (AllowPrivateAccess = "true"))
		USkeletalMeshComponent *FP_Arms;

		UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Soldier, meta = (AllowPrivateAccess = "true"))
		USkeletalMeshComponent *FP_Foots;

		UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Soldier, meta = (AllowPrivateAccess = "true"))
		USkeletalMeshComponent *FP_Legs;

		UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Soldier, meta = (AllowPrivateAccess = "true"))
		USkeletalMeshComponent* TP_Gun;

		UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Soldier, meta = (AllowPrivateAccess = "true"))
		UChildActorComponent *FP_PrimaryGun;

		UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Soldier, meta = (AllowPrivateAccess = "true"))
		UChildActorComponent *FP_SecondaryGun;

		UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Soldier, meta = (AllowPrivateAccess = "true"))
		UStaticMeshComponent* TP_MuzzleMesh;
		
		UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Soldier, meta = (AllowPrivateAccess = "true"))
		UStaticMeshComponent* TP_SightMesh;

		UPROPERTY()
		USoldierInterfaceWidget *SoldierInterfaceWidget;

		UPROPERTY(EditAnywhere, Category = Soldier, meta = (AllowPrivateAccess = "true"))
		TSubclassOf<USoldierInterfaceWidget> TSoldierInterfaceWidget;

		UPROPERTY(EditAnywhere, Category = Soldier, meta = (AllowPrivateAccess = "true"))
		TSubclassOf<UWeaponCustomizeWidget> TWeaponCustomizeWidget;

		UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Soldier, meta = (AllowPrivateAccess = "true"))
		UCurveFloat* PitchCurve;

		UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Soldier, meta = (AllowPrivateAccess = "true"))
		UCurveFloat* YawCurve;

		UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Soldier, meta = (AllowPrivateAccess = "true"))
		UCurveFloat* ADS_Curve;

		UPROPERTY()
		FTimeline RecoilTimeline;

		UPROPERTY()
		FTimeline ADS_Timeline;

		FRotator RecoilStartRotation;
		FRotator RecoilEndRotation;
		float yawInput;
		float pitchInput;
		float clipDistance;
		const float BaseTurnRate = 45.f;
		const float BaseLookUpRate = 45.f;
		const float FOV_Start = 95.f;
		const float FOV_End = 50.f;
		FVector FP_ArmVecStart = FVector(-0.172258, 2.895133, -162.847717);
		FRotator FP_ArmRotStart = FRotator(0.00, -89.99, 0.00);
		bool bAimDownSight;
		bool bSprint;
		bool bWeaponCustomize;
		bool bReloading;
		bool bIsSecondWeapon;
		bool bSoldierWidgetInterfaceSee;
		bool bWeaponIsClipping;
		IBaseWeaponInterface *currentRightHandWeapon;
		ABaseMagazine* currentGetMagazineOwner;
		FTimerHandle T_FP_ArmFireAnimationHandle;
		FTimerHandle T_FireModeHandle;
		FTimerHandle T_WeaponSwayHandle;
		FTimerHandle T_SoldierWidgetInterfaceHandle;
		FTimerHandle T_WeaponClippingHandle;
		uint8 currentWeaponFireMode;
		uint8 SemiAutoFireCount = 0;
		TArray<USceneComponent*> GunChildComponents;
		TSubclassOf<UCameraShakeBase> TCameraShake;
};