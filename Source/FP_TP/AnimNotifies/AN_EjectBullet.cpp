#include "AN_EjectBullet.h"
#include "../Weapons/BaseWeaponInterface.h"

void UAN_EjectBullet::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation){
	Super::Notify(MeshComp, Animation);

	IBaseWeaponInterface* weapon = Cast<IBaseWeaponInterface>(MeshComp->GetOwner());
	if (weapon){
		weapon->SpawnEjectBullet();
	}
}
