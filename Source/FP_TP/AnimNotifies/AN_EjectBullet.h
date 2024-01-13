#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "AN_EjectBullet.generated.h"

UCLASS()
class FP_TP_API UAN_EjectBullet : public UAnimNotify{
	public:
		virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;
	private:
		GENERATED_BODY()
	
};
