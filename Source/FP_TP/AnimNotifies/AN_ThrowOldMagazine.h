#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "AN_ThrowOldMagazine.generated.h"

class ASoldier;

UCLASS()
class FP_TP_API UAN_ThrowOldMagazine : public UAnimNotify{
	public:
		virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;

	private:
		GENERATED_BODY()
		ASoldier *Soldier;
};
