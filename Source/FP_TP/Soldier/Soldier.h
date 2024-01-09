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
class USoldierMenuWidget;

class IBaseWeaponInterface;

UCLASS()
class FP_TP_API ASoldier : public ACharacter{
	public:
		ASoldier();
		FORCEINLINE bool GetAimDownSightState() const { return bAimDownSight; }
		FORCEINLINE USkeletalMeshComponent *GetTPGunMesh() const { return TP_Gun; }
		FORCEINLINE USkeletalMeshComponent *GetFPArm() const { return FP_Arms; }
		FORCEINLINE void SetCurrentFPRightHandWeapon(IBaseWeaponInterface* newWeapon) { currentRightHandWeapon = newWeapon; }
		FORCEINLINE IBaseWeaponInterface *GetCurrentFPRightHandWeapon() const { return currentRightHandWeapon; }

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
		FORCEINLINE FVector SelectVector(const FVector &A, const FVector &B, const bool &bSelectA) const { return bSelectA ? A : B; }
		FORCEINLINE FRotator FindLookAtRotation(const FVector &Start, const FVector &Target) { return FRotationMatrix::MakeFromX(Target - Start).Rotator(); }
		FORCEINLINE FRotator DeltaRotator(const FRotator& A, const FRotator& B) { return (A - B).GetNormalized(); }
		
		UFUNCTION()
		void AimDownSightUpdate(float Alpha);
		
		UFUNCTION()
		void OnAimDownSightFinished();

		UFUNCTION()
		void RecoilStartPitch(float Alpha);

		UFUNCTION()
		void RecoilStartYaw(float Alpha);

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

		UPROPERTY()
		USoldierMenuWidget* SoldierMenuWidget;

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
		const float BaseTurnRate = 45.f;
		const float BaseLookUpRate = 45.f;
		const float FOV_Start = 95.f;
		const float FOV_End = 45.f;

		const FVector FP_ArmVecStart = FVector(-0.172258, 2.895133, -162.847717);
		const FRotator FP_ArmRotStart = FRotator(0.00, -89.99, 0.00);

		bool bAimDownSight;
		bool bSprint;

		IBaseWeaponInterface *currentRightHandWeapon;

		FTimerHandle T_FP_ArmFireAnimationHandle;
		FTimerHandle T_FireModeHandle;

		uint8 currentWeaponFireMode;
		uint8 SemiAutoFireCount = 0;

		TSubclassOf<UCameraShakeBase> TCameraShake;
		TSubclassOf<USoldierMenuWidget> TSoldierMenuWidget;
};