#include "FP_Rifle_AN_GetOldMagazine.h"
#include "../Soldier/Soldier.h"
#include "../Weapons/BaseWeaponInterface.h"
#include "../Weapons/BaseMagazine.h"

void UFP_Rifle_AnimNotifyGetOldMagazine::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation){
	Super::Notify(MeshComp, Animation);
	Soldier = Cast<ASoldier>(MeshComp->GetOwner());
	if (Soldier) {
		Soldier->GetCurrentFPRightHandWeapon()->GetWeaponMesh()->HideBoneByName(FName(Soldier->GetCurrentFPRightHandWeapon()->GetWeaponMagazineBoneName()), EPhysBodyOp::PBO_None);
		Soldier->GetTPGunMesh()->HideBoneByName(FName(Soldier->GetCurrentFPRightHandWeapon()->GetWeaponMagazineBoneName()), EPhysBodyOp::PBO_None);
		const FTransform LeftHandSocketTransform = Soldier->GetFPArm()->GetSocketTransform(FName("leftHand"));
		FActorSpawnParameters SpawnParams;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		ABaseMagazine *magazine = MeshComp->GetOwner()->GetWorld()->SpawnActor<ABaseMagazine>(Soldier->GetCurrentFPRightHandWeapon()->GetWeaponMagazine(), LeftHandSocketTransform, SpawnParams);
		if (magazine) {
			magazine->SetMagazineMesh(EWeaponMagazineType::EMPTY);
			magazine->GetMagazineMesh()->AttachToComponent(Soldier->GetFPArm(), FAttachmentTransformRules::SnapToTargetIncludingScale, FName("leftHand"));
			Soldier->SetPreviousMagazineOwner(magazine);
			magazine->GetMagazineMesh()->GetOwner()->SetOwner(Soldier->GetFPArm()->GetOwner());
			magazine->GetMagazineMesh()->SetCastShadow(false);
			magazine->GetMagazineMesh()->bOnlyOwnerSee = true;

		}
	}
}
