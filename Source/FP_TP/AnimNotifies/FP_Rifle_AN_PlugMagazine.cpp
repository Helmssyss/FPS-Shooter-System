#include "FP_Rifle_AN_PlugMagazine.h"
#include "../Soldier/Soldier.h"
#include "../Weapons/BaseWeaponInterface.h"
#include "../Weapons/BaseMagazine.h"
#include "Kismet/GameplayStatics.h"

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
			ABaseMagazine* magazine = Cast<ABaseMagazine>(i->GetOwner());
			if (magazine) {
				magazine->GetOwner()->SetOwner(Soldier->GetPreviousMagazineOwner());
				UGameplayStatics::PlaySound2D(MeshComp->GetOwner()->GetWorld(), LoadObject<USoundBase>(nullptr, TEXT("/Game/Weapons/FX/Sounds/Rifle/Wavs/Rifle_Reload_Insert")));
				magazine->Destroy();
				Soldier->GetCurrentFPRightHandWeapon()->ReloadWeapon();
			}
		}
	}

}
