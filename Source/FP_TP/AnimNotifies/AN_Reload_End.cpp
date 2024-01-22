#include "AN_Reload_End.h"
#include "../Soldier/Soldier.h"

void UAN_Reload_End::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation){
	Super::Notify(MeshComp, Animation);

	Soldier = Cast<ASoldier>(MeshComp->GetOwner());
	if (Soldier)
		Soldier->SetReloadState(false);
}
