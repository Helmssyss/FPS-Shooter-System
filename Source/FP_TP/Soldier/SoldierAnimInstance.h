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
	private:
		GENERATED_BODY()
		virtual void NativeUpdateAnimation(float DeltaSeconds) override;
		FRotator GetLookRotation(ASoldier* soldier);
		FRotator InverseTransformRotation(const FTransform& Transform, FRotator Rotation);

		UPROPERTY(BlueprintReadonly, Category = Soldier, meta = (AllowPrivateAccess = "true"))
		FRotator SoldierHeadRotation;
};
