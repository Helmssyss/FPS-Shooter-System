#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseMagazine.h"
#include "WeaponEnums.h"
#include "Magazine_PistolDeagle.generated.h"

class UStaticMeshComponent;

UCLASS()
class FP_TP_API AMagazine_PistolDeagle : public ABaseMagazine {
	public:	
		AMagazine_PistolDeagle();
		virtual UStaticMeshComponent* GetMagazineMesh() override { return magazineMesh; }
		virtual void SetMagazineMesh(EWeaponMagazineType magazineType) override;

	private:
		GENERATED_BODY()
		UStaticMeshComponent* magazineMesh;
};
