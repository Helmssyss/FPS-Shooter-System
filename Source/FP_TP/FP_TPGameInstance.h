#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "./Widgets/WidgetEnums.h"
#include "FP_TPGameInstance.generated.h"

class ASoldier;

UCLASS()
class FP_TP_API UFP_TPGameInstance : public UGameInstance{
	public:
		UClass *SoldierStaticClass;
		ESoldierClasses selectSoldierClass;
		ESoldierSelectWepon selectWeaponClass;
		ASoldier *SoldierRef;

	private:
		GENERATED_BODY()
};
