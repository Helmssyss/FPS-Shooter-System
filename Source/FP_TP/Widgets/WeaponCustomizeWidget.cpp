#include "WeaponCustomizeWidget.h"
#include "../Soldier/Soldier.h"
#include "../Weapons/BaseWeaponInterface.h"
#include "./FP_TP/FP_TPGameInstance.h"
#include "Components/StaticMeshComponent.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"

#define printf(color,format,...) GEngine->AddOnScreenDebugMessage(-1, 3, color, FString::Printf(TEXT(format), ##__VA_ARGS__));

void UWeaponCustomizeWidget::NativeOnInitialized(){
	GameInstance = Cast<UFP_TPGameInstance>(GetGameInstance());
	SelectSuppressor->OnClicked.AddDynamic(this, &UWeaponCustomizeWidget::SetSelectSuppressor);
	UnSelectSuppressor->OnClicked.AddDynamic(this, &UWeaponCustomizeWidget::SetUnSelectSuppressor);
	SelectRedDotSight->OnClicked.AddDynamic(this, &UWeaponCustomizeWidget::SetSelectRedDotSight);
	UnSelectSight->OnClicked.AddDynamic(this, &UWeaponCustomizeWidget::SetUnSelectSight);
}

void UWeaponCustomizeWidget::SetSelectSuppressor(){
	if (GameInstance->SoldierRef) {
		GameInstance->SoldierRef->GetCurrentFPRightHandWeapon()->SetWeaponMuzzleType(EWeaponMuzzleType::SUPPRESSOR);
		GameInstance->SoldierRef->GetCurrentFPRightHandWeapon()->GetWeaponCustomizeMuzzle()->SetStaticMesh(LoadObject<UStaticMesh>(nullptr, TEXT("/Game/Weapons/Meshes/Accessories/SM_Suppressor5")));
		GameInstance->SoldierRef->GetTPGunMuzzleMesh()->SetStaticMesh(LoadObject<UStaticMesh>(nullptr, TEXT("/Game/Weapons/Meshes/Accessories/SM_Suppressor5")));
		UGameplayStatics::PlaySound2D(this, LoadObject<USoundBase>(nullptr, TEXT("/Game/Weapons/FX/Sounds/Pistol/Wavs/Pistol_ReloadMagEject01")));
		SelectSuppressor->SetIsEnabled(false);
		UnSelectSuppressor->SetIsEnabled(true);
	}
}

void UWeaponCustomizeWidget::SetUnSelectSuppressor(){
	if (GameInstance->SoldierRef) {
		GameInstance->SoldierRef->GetCurrentFPRightHandWeapon()->SetWeaponMuzzleType(EWeaponMuzzleType::NORMAL);
		GameInstance->SoldierRef->GetCurrentFPRightHandWeapon()->GetWeaponCustomizeMuzzle()->SetStaticMesh(nullptr);
		GameInstance->SoldierRef->GetTPGunMuzzleMesh()->SetStaticMesh(nullptr);
		UGameplayStatics::PlaySound2D(this, LoadObject<USoundBase>(nullptr, TEXT("/Game/Weapons/FX/Sounds/Pistol/Wavs/Pistol_ReloadMagEject02")));
		SelectSuppressor->SetIsEnabled(true);
		UnSelectSuppressor->SetIsEnabled(false);
	}
}

void UWeaponCustomizeWidget::SetSelectRedDotSight(){
	if (GameInstance->SoldierRef) {
		GameInstance->SoldierRef->GetCurrentFPRightHandWeapon()->SetWeaponSightType(EWeaponSightType::RED_DOT);
		GameInstance->SoldierRef->GetCurrentFPRightHandWeapon()->GetWeaponCustomizeSight()->SetStaticMesh(LoadObject<UStaticMesh>(nullptr, TEXT("/Game/Weapons/Meshes/Accessories/SM_T4_Sight")));
		GameInstance->SoldierRef->GetTPGunSightMesh()->SetStaticMesh(LoadObject<UStaticMesh>(nullptr, TEXT("/Game/Weapons/Meshes/Accessories/SM_T4_Sight")));
		UGameplayStatics::PlaySound2D(this, LoadObject<USoundBase>(nullptr, TEXT("/Game/Weapons/FX/Sounds/Pistol/Wavs/Pistol_ReloadMagEject01")));
		SelectRedDotSight->SetIsEnabled(false);
		UnSelectSight->SetIsEnabled(true);
	}
}

void UWeaponCustomizeWidget::SetUnSelectSight(){
	if (GameInstance->SoldierRef) {
		GameInstance->SoldierRef->GetCurrentFPRightHandWeapon()->SetWeaponSightType(EWeaponSightType::IRON_SIGHT);
		GameInstance->SoldierRef->GetCurrentFPRightHandWeapon()->GetWeaponCustomizeSight()->SetStaticMesh(nullptr);
		GameInstance->SoldierRef->GetTPGunSightMesh()->SetStaticMesh(nullptr);
		UGameplayStatics::PlaySound2D(this, LoadObject<USoundBase>(nullptr, TEXT("/Game/Weapons/FX/Sounds/Pistol/Wavs/Pistol_ReloadMagEject02")));
		SelectRedDotSight->SetIsEnabled(true);
		UnSelectSight->SetIsEnabled(false);
	}
}