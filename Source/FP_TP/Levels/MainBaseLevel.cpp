#include "MainBaseLevel.h"
#include "./FP_TP/FP_TPGameInstance.h"
#include "../Widgets/WidgetEnums.h"
#include "../Soldier/Soldier.h"
#include "../Weapons/BaseWeaponInterface.h"
#include "../Weapons/RifleAR4.h"
#include "../Weapons/RifleAK.h"
#include "../Weapons/PistolDeagle.h"

#include "GameFramework/CharacterMovementComponent.h"
#include "UObject/ConstructorHelpers.h"

#define  printf(color,format,...) GEngine->AddOnScreenDebugMessage(-1, 30, color, FString::Printf(TEXT(format), ##__VA_ARGS__));

AMainBaseLevel::AMainBaseLevel(){}

void AMainBaseLevel::BeginPlay(){
	Super::BeginPlay();
	UFP_TPGameInstance *GameInstance = Cast<UFP_TPGameInstance>(GetGameInstance());
	if (GameInstance) {
		FActorSpawnParameters sParams;
		sParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		const FTransform SpawnTransform(FRotator::ZeroRotator, FVector(-1601.019287, -861.003052, 300.603363), FVector(1, 1, 1));
		spawnedSoldier = GetWorld()->SpawnActor<ASoldier>(GameInstance->SoldierStaticClass, SpawnTransform, sParams);
		if (spawnedSoldier){
			APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
			if (PlayerController) {
				PlayerController->Possess(spawnedSoldier);
				SetSpawnWeapon(GameInstance, PlayerController);
			}
			GameInstance->SoldierRef = spawnedSoldier;
			printf(FColor::Red,"SelectSoldierClass -> %i" ,GameInstance->selectSoldierClass);
		}
	}
}

void AMainBaseLevel::SetSpawnWeapon(UFP_TPGameInstance* &gameInstance, APlayerController* &playerController){
	TArray<USceneComponent*> ChildComponents;
	const FTransform SpawnTransform(FRotator::ZeroRotator, FVector(-1601.019287, -861.003052, 300.603363), FVector(1, 1, 1));
	FActorSpawnParameters sParams;
	sParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	switch (gameInstance->selectSoldierClass) {
		case ESoldierClasses::ASSAULT:{
			if (gameInstance->selectWeaponClass == ESoldierSelectWepon::WEAPON_AR4) {
				rifleGun = ARifleAR4::StaticClass();
				pistolGun = APistolDeagle::StaticClass();
				spawnedSoldier->GetFPPrimaryGun()->SetChildActorClass(rifleGun);
				spawnedSoldier->GetFPSecondaryGun()->SetChildActorClass(pistolGun);
				spawnedSoldier->GetFPSecondaryGun()->SetVisibility(false);
				SetWeaponSettings(ChildComponents);
			}

			else if (gameInstance->selectWeaponClass == ESoldierSelectWepon::WEAPON_AK47) {
				rifleGun = ARifleAK::StaticClass();
				pistolGun = APistolDeagle::StaticClass();
				spawnedSoldier->GetFPPrimaryGun()->SetChildActorClass(rifleGun);
				spawnedSoldier->GetFPSecondaryGun()->SetChildActorClass(pistolGun);
				spawnedSoldier->GetFPSecondaryGun()->SetVisibility(false);
				SetWeaponSettings(ChildComponents);
			}
			break;
		}
		case ESoldierClasses::SUPPORT: {
			break;
		}

		case ESoldierClasses::RECON:
			break;
	}

	if (IBaseWeaponInterface* currentRightHandWeapon = Cast<IBaseWeaponInterface>(spawnedSoldier->GetFPPrimaryGun()->GetChildActor())) {
		spawnedSoldier->SetCurrentFPRightHandWeapon(currentRightHandWeapon);
		for (UStaticMeshComponent* &i : spawnedSoldier->GetCurrentFPRightHandWeapon()->GetWeaponCosmetics().CosmeticComponents) {
			i->bOnlyOwnerSee = true;
			i->SetCastShadow(false);
		}
	}
}

void AMainBaseLevel::SetWeaponSettings(TArray<USceneComponent*> &ChildComponents){
	spawnedSoldier->GetFPPrimaryGun()->GetChildrenComponents(false, ChildComponents);
	for (USceneComponent* component : ChildComponents) {
		if (USkeletalMeshComponent* componentRifleMesh = Cast<USkeletalMeshComponent>(component)) {
			spawnedSoldier->GetTPGunMesh()->SetSkeletalMesh(componentRifleMesh->SkeletalMesh);
			componentRifleMesh->SetCastShadow(false);
			componentRifleMesh->GetOwner()->SetOwner(spawnedSoldier->GetFPArm()->GetOwner());
			componentRifleMesh->bOnlyOwnerSee = true;
			printf(FColor::Cyan, "component -> %s", *component->GetName());
		}
	}
	spawnedSoldier->GetFPSecondaryGun()->GetChildrenComponents(false, ChildComponents);
	for (USceneComponent* component : ChildComponents) {
		if (USkeletalMeshComponent* componentPistolMesh = Cast<USkeletalMeshComponent>(component)) {
			componentPistolMesh->SetCastShadow(false);
			componentPistolMesh->GetOwner()->SetOwner(spawnedSoldier->GetFPArm()->GetOwner());
			componentPistolMesh->bOnlyOwnerSee = true;
			printf(FColor::Cyan, "component -> %s", *component->GetName());
		}
	}
}
