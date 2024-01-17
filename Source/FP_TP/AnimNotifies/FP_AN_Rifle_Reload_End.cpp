#include "FP_AN_Rifle_Reload_End.h"
#include "../Soldier/Soldier.h"

void UFP_AN_Rifle_Reload_End::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation){
	Super::Notify(MeshComp, Animation);

	Soldier = Cast<ASoldier>(MeshComp->GetOwner());
	if (Soldier)
		Soldier->SetReloadState(false);
}
