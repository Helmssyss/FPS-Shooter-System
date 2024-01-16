#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseMagazine.h"
#include "WeaponEnums.h"
#include "Magazine_AK47.generated.h"

class UStaticMeshComponent;

UCLASS()
class FP_TP_API AMagazine_AK47 : public ABaseMagazine {

	public:
		AMagazine_AK47();
		virtual UStaticMeshComponent* GetMagazineMesh() override { return magazineMesh; }
		virtual void SetMagazineMesh(EWeaponMagazineType magazineType) override;

	private:
		GENERATED_BODY()
		UStaticMeshComponent *magazineMesh;
};
