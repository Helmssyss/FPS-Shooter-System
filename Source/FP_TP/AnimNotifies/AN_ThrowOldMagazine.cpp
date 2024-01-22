#include "AN_ThrowOldMagazine.h"
#include "../Soldier/Soldier.h"
#include "../Weapons/BaseWeaponInterface.h"
#include "../Weapons/BaseMagazine.h"

#include "Components/StaticMeshComponent.h"

#define printf(color,format,...) GEngine->AddOnScreenDebugMessage(-1, 2, color, FString::Printf(TEXT(format), ##__VA_ARGS__));

void UAN_ThrowOldMagazine::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) {
	Super::Notify(MeshComp, Animation);

	Soldier = Cast<ASoldier>(MeshComp->GetOwner());
	if (Soldier) {
		const FTransform LeftHandSocketTransform = Soldier->GetFPArm()->GetSocketTransform(FName("leftHand"));
		TArray<USceneComponent*> childrenComponents;
		Soldier->GetFPArm()->GetChildrenComponents(false, childrenComponents);
		for (USceneComponent* i : childrenComponents) {			
			ABaseMagazine* Magazine = Cast<ABaseMagazine>(i->GetOwner());
			if (Magazine) {
				Magazine->GetOwner()->SetOwner(Soldier->GetPreviousMagazineOwner());
				Magazine->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
				Magazine->GetMagazineMesh()->SetCastShadow(true);
				Magazine->GetMagazineMesh()->bOnlyOwnerSee = false;
				Magazine->GetMagazineMesh()->SetSimulatePhysics(true);
				Magazine->GetMagazineMesh()->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);
				Magazine->SetLifeSpan(3);
			}
		}
	}
}