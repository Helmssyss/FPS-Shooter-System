#include "MainBaseLevel.h"
#include "./FP_TP/FP_TPGameInstance.h"
#include "../Widgets/WidgetEnums.h"
#include "../Soldier/Soldier.h"
#include "../Weapons/BaseWeaponInterface.h"
#include "../Weapons/RifleAR4.h"
#include "../Weapons/RifleMAC11.h"

#include "GameFramework/CharacterMovementComponent.h"
#include "UObject/ConstructorHelpers.h"

#define  printf(color,format,...) GEngine->AddOnScreenDebugMessage(-1, 30, color, FString::Printf(TEXT(format), ##__VA_ARGS__));

AMainBaseLevel::AMainBaseLevel(){
}

void AMainBaseLevel::BeginPlay(){
	Super::BeginPlay();
	const UFP_TPGameInstance *GameInstance = Cast<UFP_TPGameInstance>(GetGameInstance());
	if (GameInstance) {
		FActorSpawnParameters sParams;
		sParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		const FTransform SpawnTransform(FRotator::ZeroRotator, FVector(-1601.019287, -861.003052, 300.603363), FVector(1, 1, 1));
		spawnedSoldier = GetWorld()->SpawnActor<ASoldier>(GameInstance->SoldierStaticClass, SpawnTransform, sParams);
		if (spawnedSoldier){
			spawnedSoldier->GetCharacterMovement()->MaxWalkSpeed = GameInstance->SoldierSpeed;
			GEngine->AddOnScreenDebugMessage(-1, 2, FColor::Cyan, FString("KARAKTER DOGDU"));
			APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();

			if (PlayerController) {
				PlayerController->Possess(spawnedSoldier);
				SetSpawnWeapon(GameInstance, PlayerController);
			}
			printf(FColor::Red,"SelectSoldierClass -> %i" ,GameInstance->selectSoldierClass);
		}
	}
}

void AMainBaseLevel::SetSpawnWeapon(const UFP_TPGameInstance* &gameInstance, APlayerController* &playerController){
	const FTransform SpawnTransform(FRotator::ZeroRotator, FVector(-1601.019287, -861.003052, 300.603363), FVector(1, 1, 1));
	FActorSpawnParameters sParams;
	sParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	switch (gameInstance->selectSoldierClass) {
		case ESoldierClasses::ASSAULT:{
			IBaseWeaponInterface* weapon = GetWorld()->SpawnActor<ARifleAR4>(ARifleAR4::StaticClass(), SpawnTransform, sParams);
			if (weapon) {
				weapon->GetWeaponMesh()->AttachToComponent(spawnedSoldier->GetFPArm(), FAttachmentTransformRules::SnapToTargetIncludingScale, FName("FP_rightHand"));
				spawnedSoldier->GetTPGunMesh()->SetSkeletalMesh(weapon->GetWeaponMeshObject());
				spawnedSoldier->SetCurrentFPRightHandWeapon(weapon);
				weapon->GetWeaponMesh()->SetCastShadow(false);
				weapon->GetWeaponMesh()->GetOwner()->SetOwner(spawnedSoldier->GetFPArm()->GetOwner());
				weapon->GetWeaponMesh()->bOnlyOwnerSee = true;
			}
			break;
		}
		case ESoldierClasses::SUPPORT: {
			//IBaseWeaponInterface* weapon = GetWorld()->SpawnActor<ARifleMAC11>(ARifleMAC11::StaticClass(), SpawnTransform, sParams);
			//if (weapon) {
			//	weapon->GetWeaponMesh()->AttachToComponent(spawnedSoldier->GetFPArm(), FAttachmentTransformRules::SnapToTargetIncludingScale, FName("FP_rightHand"));
			//	spawnedSoldier->GetTPGunMesh()->SetSkeletalMesh(weapon->GetWeaponMeshObject());
			//	weapon->GetWeaponMesh()->SetCastShadow(false);
			//	weapon->GetWeaponMesh()->GetOwner()->SetOwner(spawnedSoldier->GetFPArm()->GetOwner());
			//	weapon->GetWeaponMesh()->bOnlyOwnerSee = true;
			//	spawnedSoldier->SetCurrentFPRightHandWeapon(weapon);
			//}
			break;
		}

		case ESoldierClasses::RECON:
			break;
	}
}