
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WeaponEnums.h"
#include "BaseMagazine.generated.h"

class USoundBase;
class UStaticMeshComponent;

UCLASS()
class FP_TP_API ABaseMagazine : public AActor{
	public:	
		ABaseMagazine();
		virtual UStaticMeshComponent* GetMagazineMesh() { return nullptr; }
		virtual void SetMagazineMesh(EWeaponMagazineType magazineType){};

	private:
		GENERATED_BODY()

		virtual void BeginPlay() override;
};
