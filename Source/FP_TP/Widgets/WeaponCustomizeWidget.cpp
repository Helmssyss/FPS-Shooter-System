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
		FWeaponCosmetics cosmetic = GameInstance->SoldierRef->GetCurrentFPRightHandWeapon()->GetWeaponCosmetics();
		cosmetic.MuzzleMesh = LoadObject<UStaticMesh>(nullptr, TEXT("/Game/Weapons/Meshes/Accessories/SM_Suppressor5"));
		cosmetic.MuzzleType = EWeaponMuzzleType::SUPPRESSOR;
		GameInstance->SoldierRef->GetCurrentFPRightHandWeapon()->SetWeaponCosmetics(cosmetic);
		GameInstance->SoldierRef->SetSelectWeaponCosmetics();
		UGameplayStatics::PlaySound2D(this, LoadObject<USoundBase>(nullptr, TEXT("/Game/Weapons/FX/Sounds/Pistol/Wavs/Pistol_ReloadMagEject01")));
		SelectSuppressor->SetIsEnabled(false);
		UnSelectSuppressor->SetIsEnabled(true);
	}
}

void UWeaponCustomizeWidget::SetUnSelectSuppressor(){
	if (GameInstance->SoldierRef) {
		FWeaponCosmetics cosmetic = GameInstance->SoldierRef->GetCurrentFPRightHandWeapon()->GetWeaponCosmetics();
		cosmetic.MuzzleMesh = nullptr;
		cosmetic.MuzzleType = EWeaponMuzzleType::NORMAL;
		GameInstance->SoldierRef->GetCurrentFPRightHandWeapon()->SetWeaponCosmetics(cosmetic);
		GameInstance->SoldierRef->SetSelectWeaponCosmetics();
		UGameplayStatics::PlaySound2D(this, LoadObject<USoundBase>(nullptr, TEXT("/Game/Weapons/FX/Sounds/Pistol/Wavs/Pistol_ReloadMagEject02")));
		SelectSuppressor->SetIsEnabled(true);
		UnSelectSuppressor->SetIsEnabled(false);
	}
}

void UWeaponCustomizeWidget::SetSelectRedDotSight(){
	if (GameInstance->SoldierRef) {
		FWeaponCosmetics cosmetic = GameInstance->SoldierRef->GetCurrentFPRightHandWeapon()->GetWeaponCosmetics();
		cosmetic.SightMesh = LoadObject<UStaticMesh>(nullptr, TEXT("/Game/Weapons/Meshes/Accessories/SM_T4_Sight"));
		cosmetic.SightType = EWeaponSightType::RED_DOT;
		GameInstance->SoldierRef->GetCurrentFPRightHandWeapon()->SetWeaponCosmetics(cosmetic);
		GameInstance->SoldierRef->SetSelectWeaponCosmetics();
		UGameplayStatics::PlaySound2D(this, LoadObject<USoundBase>(nullptr, TEXT("/Game/Weapons/FX/Sounds/Pistol/Wavs/Pistol_ReloadMagEject01")));
		SelectRedDotSight->SetIsEnabled(false);
		UnSelectSight->SetIsEnabled(true);
	}
}

void UWeaponCustomizeWidget::SetUnSelectSight(){
	if (GameInstance->SoldierRef) {
		FWeaponCosmetics cosmetic = GameInstance->SoldierRef->GetCurrentFPRightHandWeapon()->GetWeaponCosmetics();
		cosmetic.SightMesh = nullptr;
		cosmetic.SightType = EWeaponSightType::IRON_SIGHT;
		GameInstance->SoldierRef->GetCurrentFPRightHandWeapon()->SetWeaponCosmetics(cosmetic);
		GameInstance->SoldierRef->SetSelectWeaponCosmetics();
		UGameplayStatics::PlaySound2D(this, LoadObject<USoundBase>(nullptr, TEXT("/Game/Weapons/FX/Sounds/Pistol/Wavs/Pistol_ReloadMagEject02")));
		SelectRedDotSight->SetIsEnabled(true);
		UnSelectSight->SetIsEnabled(false);
	}
}