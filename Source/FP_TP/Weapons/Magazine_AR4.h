#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseMagazine.h"
#include "WeaponEnums.h"
#include "Magazine_AR4.generated.h"

class UStaticMeshComponent;

UCLASS()
class FP_TP_API AMagazine_AR4 : public ABaseMagazine {
	public:
		AMagazine_AR4();
		virtual UStaticMeshComponent* GetMagazineMesh() override { return magazineMesh; }
		virtual void SetMagazineMesh(EWeaponMagazineType magazineType) override;

	private:
		GENERATED_BODY()
		//virtual void BeginPlay() override;
		UStaticMeshComponent* magazineMesh;

};
