#include "SoldierMenuWidget.h"
#include "../Soldier/Soldier.h"
#include "../Weapons/BaseWeaponInterface.h"

#include "Components/TextBlock.h"
#include "Components/Image.h"

void USoldierMenuWidget::NativeConstruct(){
	Super::NativeConstruct();
	Soldier = Cast<ASoldier>(GetOwningPlayerPawn());
}

bool USoldierMenuWidget::Initialize(){
	const bool initialize = Super::Initialize();
	WeaponCurrentAmmo->TextDelegate.BindUFunction(this, "ViewWeaponCurrentAmmo");
	WeaponName->TextDelegate.BindUFunction(this, "ViewWeaponName");
	WeaponTotalAmmo->TextDelegate.BindUFunction(this, "ViewWeaponTotalAmmo");
	WeaponImage->BrushDelegate.BindUFunction(this, "ViewWeaponImage");
	FireModeImage->BrushDelegate.BindUFunction(this, "ViewWeaponFireMode");
	if (!initialize)
		return false;

	return true;
}

FText USoldierMenuWidget::ViewWeaponCurrentAmmo(){
	if (Soldier) {
		if (Soldier->GetCurrentFPRightHandWeapon())
			return FText::FromString(FString::FromInt(Soldier->GetCurrentFPRightHandWeapon()->GetCurrentAmmo()));
		else
			return FText::GetEmpty();
	}else
		return FText::GetEmpty();
}

FText USoldierMenuWidget::ViewWeaponTotalAmmo(){
	if (Soldier) {
		if (Soldier->GetCurrentFPRightHandWeapon())
			return FText::FromString(FString::FromInt(Soldier->GetCurrentFPRightHandWeapon()->GetTotalAmmo()));
		else
			return FText::GetEmpty();
	}else
		return FText::GetEmpty();
}

FText USoldierMenuWidget::ViewWeaponName(){
	if (Soldier) {
		if (Soldier->GetCurrentFPRightHandWeapon())
			return FText::FromString(Soldier->GetCurrentFPRightHandWeapon()->GetWeaponName());
		else
			return FText::GetEmpty();
	}else
		return FText::GetEmpty();
}

FSlateBrush USoldierMenuWidget::ViewWeaponImage(){
	if (Soldier) {
		if (Soldier->GetCurrentFPRightHandWeapon()) {
			FSlateBrush Brush = WeaponImage->Brush;
			Brush.SetResourceObject(Soldier->GetCurrentFPRightHandWeapon()->GetWeaponTexture());
			WeaponImage->SetBrush(Brush);
			WeaponImage->SetVisibility(ESlateVisibility::Visible);
			return Brush;
		}else {
			FSlateBrush _;
			return _;
		}
	}else {
		FSlateBrush _;
		return _;
	}
}

FSlateBrush USoldierMenuWidget::ViewWeaponFireMode(){
	if (Soldier) {
		if (Soldier->GetCurrentFPRightHandWeapon()) {
			FSlateBrush Brush = FireModeImage->Brush;
			Brush.SetResourceObject(Soldier->GetCurrentFPRightHandWeapon()->GetWeaponFireModeTexture(Soldier->GetCurrentFPRightHandWeapon()->GetCurrentWeaponFireMode()));
			FireModeImage->SetBrush(Brush);
			FireModeImage->SetVisibility(ESlateVisibility::Visible);
			return Brush;
		}
		else {
			FSlateBrush _;
			return _;
		}
	}
	else {
		FSlateBrush _;
		return _;
	}
}
