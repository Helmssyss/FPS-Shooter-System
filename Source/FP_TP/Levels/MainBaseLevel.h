#pragma once

#include "CoreMinimal.h"
#include "Engine/LevelScriptActor.h"
#include "MainBaseLevel.generated.h"

class UFP_TPGameInstance;
class ASoldier;
class APlayerController;
class USkeletalMeshComponent;
class IBaseWeaponInterface;

UCLASS()
class FP_TP_API AMainBaseLevel : public ALevelScriptActor{
	public:
		AMainBaseLevel();

	private:
		GENERATED_BODY()
		virtual void BeginPlay() override;
		
		void SetSpawnWeapon(UFP_TPGameInstance* &gameInstance, APlayerController* &playerController);

		ASoldier* spawnedSoldier;
		USkeletalMeshComponent *weaponMesh;
		IBaseWeaponInterface *weapon;
	
};
