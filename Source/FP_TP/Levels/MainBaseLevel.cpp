#include "MainBaseLevel.h"
#include "./FP_TP/FP_TPGameInstance.h"
#include "../Widgets/WidgetEnums.h"
#include "../Soldier/Soldier.h"
#include "../Weapons/BaseWeaponInterface.h"
#include "../Weapons/RifleAR4.h"
#include "../Weapons/RifleMAC11.h"
#include "../Weapons/RifleAK.h"

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
			GEngine->AddOnScreenDebugMessage(-1, 2, FColor::Cyan, FString("KARAKTER DOGDU"));
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
	const FTransform SpawnTransform(FRotator::ZeroRotator, FVector(-1601.019287, -861.003052, 300.603363), FVector(1, 1, 1));
	FActorSpawnParameters sParams;
	sParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	switch (gameInstance->selectSoldierClass) {
		case ESoldierClasses::ASSAULT:{
			if (gameInstance->selectWeaponClass == ESoldierSelectWepon::WEAPON_AR4)
				weapon = GetWorld()->SpawnActor<ARifleAR4>(ARifleAR4::StaticClass(), SpawnTransform, sParams);

			else if (gameInstance->selectWeaponClass == ESoldierSelectWepon::WEAPON_AK47)
				weapon = GetWorld()->SpawnActor<ARifleAK>(ARifleAK::StaticClass(), SpawnTransform, sParams);

			if (weapon) {
				weapon->GetWeaponMesh()->AttachToComponent(spawnedSoldier->GetFPArm(), FAttachmentTransformRules::SnapToTargetIncludingScale, FName("FP_rightHand"));
				spawnedSoldier->GetTPGunMesh()->SetSkeletalMesh(weapon->GetWeaponMeshObject());
				spawnedSoldier->SetCurrentFPRightHandWeapon(weapon);
				
				weapon->GetWeaponMesh()->SetCastShadow(false);
				weapon->GetWeaponMesh()->GetOwner()->SetOwner(spawnedSoldier->GetFPArm()->GetOwner());
				weapon->GetWeaponMesh()->bOnlyOwnerSee = true;
				
				weapon->GetWeaponCustomizeSight()->bOnlyOwnerSee = true;
				weapon->GetWeaponCustomizeMuzzle()->bOnlyOwnerSee = true;
				weapon->GetWeaponCustomizeGrip()->bOnlyOwnerSee = true;

				weapon->GetWeaponCustomizeSight()->SetCastShadow(false);
				weapon->GetWeaponCustomizeMuzzle()->SetCastShadow(false);
				weapon->GetWeaponCustomizeGrip()->SetCastShadow(false);
			}
			break;
		}
		case ESoldierClasses::SUPPORT: {
			break;
		}

		case ESoldierClasses::RECON:
			break;
	}
}