#include "AN_PistolSlide.h"
#include "../Soldier/Soldier.h"
#include "../Weapons/BaseWeaponInterface.h"
#include "Kismet/GameplayStatics.h"

void UAN_PistolSlide::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation){
	Super::Notify(MeshComp, Animation);
	Soldier = Cast<ASoldier>(MeshComp->GetOwner());
	if (Soldier) {
		Soldier->GetCurrentFPRightHandWeapon()->PlayWeaponShellSetupAnimation();
		UGameplayStatics::PlaySound2D(MeshComp->GetOwner()->GetWorld(), LoadObject<USoundBase>(nullptr, TEXT("/Game/Weapons/FX/Sounds/Pistol/Wavs/Pistol_ReloadSlideRack03")));
	}
}
