#include "FP_Rifle_AN_NewSpawnMagazine.h"
#include "../Soldier/Soldier.h"
#include "../Weapons/BaseWeaponInterface.h"
#include "../Weapons/BaseMagazine.h"
#include "Kismet/GameplayStatics.h"

void UFP_Rifle_AN_NewSpawnMagazine::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation){
	Super::Notify(MeshComp, Animation);
	Soldier = Cast<ASoldier>(MeshComp->GetOwner());
	if (Soldier){
		const FTransform LeftHandSocketTransform = Soldier->GetFPArm()->GetSocketTransform(FName("leftHand"));
		FActorSpawnParameters SpawnParams;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		ABaseMagazine* magazine = MeshComp->GetOwner()->GetWorld()->SpawnActor<ABaseMagazine>(Soldier->GetCurrentFPRightHandWeapon()->GetWeaponMagazine(), LeftHandSocketTransform, SpawnParams);
		if (magazine) {
			Soldier->SetPreviousMagazineOwner(magazine);
			magazine->SetMagazineMesh(EWeaponMagazineType::FULL);
			magazine->GetMagazineMesh()->AttachToComponent(Soldier->GetFPArm(), FAttachmentTransformRules::SnapToTargetIncludingScale, FName("leftHand"));
			magazine->GetMagazineMesh()->GetOwner()->SetOwner(Soldier->GetFPArm()->GetOwner());
			magazine->GetMagazineMesh()->SetCastShadow(false);
			magazine->GetMagazineMesh()->bOnlyOwnerSee = true;
			UGameplayStatics::PlaySound2D(MeshComp->GetOwner()->GetWorld(), LoadObject<USoundBase>(nullptr, TEXT("/Game/Weapons/FX/Sounds/Rifle/Wavs/Rifle_AmmoPickup")));
		}
	}
}
