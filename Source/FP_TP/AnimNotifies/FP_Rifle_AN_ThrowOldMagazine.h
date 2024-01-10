#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "FP_Rifle_AN_ThrowOldMagazine.generated.h"

class ASoldier;

UCLASS()
class FP_TP_API UFP_Rifle_AN_ThrowOldMagazine : public UAnimNotify{
	public:
		virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;

	private:
		GENERATED_BODY()
		ASoldier *Soldier;
};
