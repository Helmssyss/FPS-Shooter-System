#pragma once
#include "CoreMinimal.h"

UENUM()
enum class ESoldierClasses : uint8 {
	ASSAULT,
	SUPPORT,
	RECON
};

UENUM()
enum class ESoldierSelectWepon : uint8 {
	WEAPON_AR4,
	WEAPON_AK47
};