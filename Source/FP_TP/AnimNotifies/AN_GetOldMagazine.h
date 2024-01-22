#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "AN_GetOldMagazine.generated.h"

class ASoldier;

UCLASS()
class FP_TP_API UAN_GetOldMagazine : public UAnimNotify{
	public:
		virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;
	
	private:
		GENERATED_BODY()

		ASoldier* Soldier;
	
};
