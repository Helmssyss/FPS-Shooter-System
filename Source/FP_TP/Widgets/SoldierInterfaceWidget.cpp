#include "SoldierInterfaceWidget.h"
#include "../Soldier/Soldier.h"
#include "../Weapons/BaseWeaponInterface.h"
#include "./FP_TP/FP_TPGameInstance.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "Kismet/GameplayStatics.h"

#define printf(color,format,...) GEngine->AddOnScreenDebugMessage(-1, 3, color, FString::Printf(TEXT(format), ##__VA_ARGS__));

void USoldierInterfaceWidget::NativeOnInitialized(){
	Super::NativeOnInitialized();
	GameInstance = Cast<UFP_TPGameInstance>(GetGameInstance());
	TotalBulletCount->TextDelegate.BindUFunction(this, "ViewTotalBulletCount");
	CurrentBulletCount->TextDelegate.BindUFunction(this, "ViewCurrentBulletCount");
	WeaponImage->BrushDelegate.BindUFunction(this, "ViewWeaponImage");
	FireModeImage->BrushDelegate.BindUFunction(this, "ViewWeaponFireMode");
}

FText USoldierInterfaceWidget::ViewTotalBulletCount() {
	if (GameInstance->SoldierRef) {
		return FText::FromString(FString::FromInt(GameInstance->SoldierRef->GetCurrentFPRightHandWeapon()->GetTotalAmmo()));
	}
	return FText::GetEmpty();
}

FText USoldierInterfaceWidget::ViewCurrentBulletCount(){
	if (GameInstance->SoldierRef) {
		return FText::FromString(FString::FromInt(GameInstance->SoldierRef->GetCurrentFPRightHandWeapon()->GetCurrentAmmo()));
	}
	return FText::GetEmpty();
}

FSlateBrush USoldierInterfaceWidget::ViewWeaponImage(){
	if (GameInstance->SoldierRef) {
		FSlateBrush Brush = WeaponImage->Brush;
		Brush.SetResourceObject(GameInstance->SoldierRef->GetCurrentFPRightHandWeapon()->GetWeaponTexture());
		WeaponImage->SetBrush(Brush);
		return Brush;
	}
	FSlateBrush _;
	return _;
}

FSlateBrush USoldierInterfaceWidget::ViewWeaponFireMode(){
	if (GameInstance->SoldierRef) {
		FSlateBrush Brush = FireModeImage->Brush;
		Brush.SetResourceObject(GameInstance->SoldierRef->GetCurrentFPRightHandWeapon()->GetWeaponFireModeTexture(GameInstance->SoldierRef->GetCurrentFPRightHandWeapon()->GetCurrentWeaponFireMode()));
		FireModeImage->SetBrush(Brush);
		return Brush;
	}
	FSlateBrush _;
	return _;
}
