#pragma once
#include "CoreMinimal.h"

UENUM()
enum class EWeaponTypes : uint8 {
	WEAPON_AR4,
	WEAPON_AK47,
	WEAPON_PISTOL
};

UENUM()
enum class EWeaponFireModes : uint8 {
	AUTO_MODE,
	SEMI_AUTO_MODE,
	SINGLE_MODE
};

UENUM()
enum class EWeaponMagazineType : uint8 {
	EMPTY,
	FULL
};

UENUM()
enum class EWeaponMuzzleType : uint8 {
	NORMAL,
	SUPPRESSOR
};

UENUM()
enum class EWeaponSightType : uint8 {
	IRON_SIGHT,
	RED_DOT
};