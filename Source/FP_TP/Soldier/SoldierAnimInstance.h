#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "SoldierAnimInstance.generated.h"

class ASoldier;

UCLASS()
class FP_TP_API USoldierAnimInstance : public UAnimInstance{
	public:
		UPROPERTY(BlueprintReadOnly, Category = Soldier)
		float soldierSpeed;

		UPROPERTY(BlueprintReadOnly, Category = Soldier)
		bool soldierIsAir;

		UPROPERTY(BlueprintReadOnly, Category = Soldier)
		float soldierDirection;

		UPROPERTY(BlueprintReadOnly, Category = Soldier)
		float soldierPitch;

		UPROPERTY(BlueprintReadOnly, Category = Soldier)
		bool soldierAimDownSight;

		UPROPERTY(BlueprintReadOnly, Category = Soldier)
		FRotator RightHandRotator;

		UPROPERTY(BlueprintReadOnly, Category = Soldier)
		FTransform LeftHandSocketTransform;

		UPROPERTY(BlueprintReadOnly, Category = Soldier)
		bool soldierReload;

		UPROPERTY(BlueprintReadOnly, Category = Soldier)
		bool soldierWeaponCustomize;

		UPROPERTY(BlueprintReadOnly, Category = Soldier)
		bool soldierSprint;

		UPROPERTY(BlueprintReadOnly, Category = Soldier)
		bool soldierIsSwitchSecondWeapon;

		UPROPERTY(BlueprintReadOnly, Category = Soldier)
		float soldierWeaponClipDistanceLast;

		UPROPERTY(BlueprintReadOnly, Category = Soldier)
		float soldierWeaponClipDistanceCurrent;

	private:
		GENERATED_BODY()
		virtual void NativeUpdateAnimation(float DeltaSeconds) override;
		FRotator GetLookRotation(ASoldier* soldier);
		FRotator InverseTransformRotation(const FTransform& Transform, FRotator Rotation);
		void WeaponSway(ASoldier* soldier);

		UPROPERTY(BlueprintReadonly, Category = Soldier, meta = (AllowPrivateAccess = "true"))
		FRotator soldierHeadRotation;

		UPROPERTY(BlueprintReadonly, Category = Soldier, meta = (AllowPrivateAccess = "true"))
		FTransform leftFPHandSocketTransform;

		UPROPERTY(BlueprintReadonly, Category = Soldier, meta = (AllowPrivateAccess = "true"))
		FTransform leftTPHandSocketTransform;
};
