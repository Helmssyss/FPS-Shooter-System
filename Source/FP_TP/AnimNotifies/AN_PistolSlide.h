#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "AN_PistolSlide.generated.h"

class ASoldier;

UCLASS()
class FP_TP_API UAN_PistolSlide : public UAnimNotify{
	public:
		virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;

	private:
		GENERATED_BODY()

		ASoldier* Soldier;
};
