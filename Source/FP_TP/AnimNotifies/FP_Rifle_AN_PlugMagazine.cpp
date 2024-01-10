#include "FP_Rifle_AN_PlugMagazine.h"
#include "../Soldier/Soldier.h"
#include "../Weapons/BaseWeaponInterface.h"
#include "../Weapons/BaseMagazine.h"

#define printf(color,format,...) GEngine->AddOnScreenDebugMessage(-1, 2, color, FString::Printf(TEXT(format), ##__VA_ARGS__));

void UFP_Rifle_AN_PlugMagazine::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation){
	Super::Notify(MeshComp, Animation);
	Soldier = Cast<ASoldier>(MeshComp->GetOwner());
	if (Soldier) {
		TArray<USceneComponent*> childrenComponents;
		Soldier->GetCurrentFPRightHandWeapon()->GetWeaponMesh()->UnHideBoneByName(FName(Soldier->GetCurrentFPRightHandWeapon()->GetWeaponMagazineBoneName()));
		Soldier->GetTPGunMesh()->UnHideBoneByName(FName(Soldier->GetCurrentFPRightHandWeapon()->GetWeaponMagazineBoneName()));
		Soldier->GetFPArm()->GetChildrenComponents(false, childrenComponents);
		for (USceneComponent* i : childrenComponents) {
			ABaseMagazine* Magazine = Cast<ABaseMagazine>(i->GetOwner());
			if (Magazine) {
				Magazine->GetOwner()->SetOwner(Soldier->GetPreviousMagazineOwner());
				Magazine->Destroy();
			}
		}
	}

}
