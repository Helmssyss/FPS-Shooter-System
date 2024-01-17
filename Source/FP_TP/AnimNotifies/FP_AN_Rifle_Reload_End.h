#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "FP_AN_Rifle_Reload_End.generated.h"

class ASoldier;

UCLASS()
class FP_TP_API UFP_AN_Rifle_Reload_End : public UAnimNotify{
	public:
		virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;

	private:
		GENERATED_BODY()
		ASoldier* Soldier;
	
};
