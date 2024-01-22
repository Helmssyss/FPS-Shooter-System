#include "SoldierInterfaceWidget.h"
#include "../Soldier/Soldier.h"
#include "../Weapons/BaseWeaponInterface.h"
#include "./FP_TP/FP_TPGameInstance.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "Components/SizeBox.h"
#include "Components/HorizontalBox.h"
#include "Components/CanvasPanelSlot.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "GameFramework/CharacterMovementComponent.h"

#define printf(color,format,...) GEngine->AddOnScreenDebugMessage(-1, 3, color, FString::Printf(TEXT(format), ##__VA_ARGS__));

void USoldierInterfaceWidget::NativeConstruct(){
	Super::NativeConstruct();

	GameInstance = Cast<UFP_TPGameInstance>(GetGameInstance());
	SlotTop = Cast<UCanvasPanelSlot>(SB_Top->Slot);
	SlotBottom = Cast<UCanvasPanelSlot>(SB_Bottom->Slot);
	SlotLeft = Cast<UCanvasPanelSlot>(SB_Left->Slot);
	SlotRight = Cast<UCanvasPanelSlot>(SB_Right->Slot);
	HPrimaryWeaponBox->SetVisibility(ESlateVisibility::Hidden);
	HSecondaryWeaponBox->SetVisibility(ESlateVisibility::Hidden);
}

void USoldierInterfaceWidget::NativeOnInitialized(){
	Super::NativeOnInitialized();
	
	TotalBulletCount->TextDelegate.BindUFunction(this, "ViewTotalBulletCount");
	CurrentBulletCount->TextDelegate.BindUFunction(this, "ViewCurrentBulletCount");
	PrimaryWeaponImage->BrushDelegate.BindUFunction(this, "ViewPrimaryWeaponImage");
	SecondaryWeaponImage->BrushDelegate.BindUFunction(this, "ViewSecondaryWeaponImage");
	FireModeImage->BrushDelegate.BindUFunction(this, "ViewWeaponFireMode");
	GetWorld()->GetTimerManager().SetTimer(TCrosshairHandle, this, &USoldierInterfaceWidget::DynamicCrosshair, 1 / UpdatedPerSecond, true);
}

FText USoldierInterfaceWidget::ViewTotalBulletCount() {
	if(GameInstance)
		if (GameInstance->SoldierRef)
			return FText::FromString(FString::FromInt(GameInstance->SoldierRef->GetCurrentFPRightHandWeapon()->GetTotalAmmo()));

	return FText::GetEmpty();
}

FText USoldierInterfaceWidget::ViewCurrentBulletCount(){
	if (GameInstance)
		if (GameInstance->SoldierRef)
		return FText::FromString(FString::FromInt(GameInstance->SoldierRef->GetCurrentFPRightHandWeapon()->GetCurrentAmmo()));
	return FText::GetEmpty();
}

FSlateBrush USoldierInterfaceWidget::ViewPrimaryWeaponImage(){
	if (GameInstance)
		if (GameInstance->SoldierRef) {
			if (IBaseWeaponInterface* Primary = Cast<IBaseWeaponInterface>(GameInstance->SoldierRef->GetFPPrimaryGun()->GetChildActor())) {
				FSlateBrush Brush = PrimaryWeaponImage->Brush;
				Brush.SetResourceObject(Primary->GetWeaponTexture());
				PrimaryWeaponImage->SetBrush(Brush);
				return Brush;
			}
		}
	FSlateBrush _;
	return _;
}

FSlateBrush USoldierInterfaceWidget::ViewSecondaryWeaponImage(){
	if (GameInstance)
		if (GameInstance->SoldierRef) {
			if (IBaseWeaponInterface* Secondary = Cast<IBaseWeaponInterface>(GameInstance->SoldierRef->GetFPSecondaryGun()->GetChildActor())) {
				FSlateBrush Brush = SecondaryWeaponImage->Brush;
				Brush.SetResourceObject(Secondary->GetWeaponTexture());
				SecondaryWeaponImage->SetBrush(Brush);
				return Brush;
			}
		}
	FSlateBrush _;
	return _;
}

FSlateBrush USoldierInterfaceWidget::ViewWeaponFireMode(){
	if (GameInstance)
		if (GameInstance->SoldierRef) {
			FSlateBrush Brush = FireModeImage->Brush;
			Brush.SetResourceObject(GameInstance->SoldierRef->GetCurrentFPRightHandWeapon()->GetWeaponFireModeTexture(GameInstance->SoldierRef->GetCurrentFPRightHandWeapon()->GetCurrentWeaponFireMode()));
			FireModeImage->SetBrush(Brush);
			return Brush;
		}
	FSlateBrush _;
	return _;
}

void USoldierInterfaceWidget::DynamicCrosshair() {
	if (GameInstance->SoldierRef->GetCurrentWeaponIsClipping()) CancelImage->SetVisibility(ESlateVisibility::Visible);
	else CancelImage->SetVisibility(ESlateVisibility::Hidden);
	
	if (SB_Top && SB_Bottom && SB_Left && SB_Right) {
		const float SoldierVelocity = GameInstance->SoldierRef->GetCharacterMovement()->Velocity.Size();
		float FixedVelocity = UKismetMathLibrary::NormalizeToRange(SoldierVelocity, 0.0f, MaxVelocity);
		FixedVelocity = FMath::Clamp(FixedVelocity, 0.f, 1.f);
		FixedVelocity *= MaxOffset;
		const FVector2D DefaultPosition(0.f, 0.f);

		if (SlotTop) {
			FVector2D Position = (FixedVelocity > 0.f) ? FVector2D(0.f, -FixedVelocity) : DefaultPosition;
			SlotTop->SetPosition(Position);
		}

		if (SlotBottom) {
			FVector2D Position = (FixedVelocity > 0.f) ? FVector2D(0.f, FixedVelocity - 5) : DefaultPosition;
			SlotBottom->SetPosition(Position);
		}

		if (SlotLeft) {
			FVector2D Position = (FixedVelocity > 0.f) ? FVector2D(-FixedVelocity, 0.f) : DefaultPosition;
			SlotLeft->SetPosition(Position);
		}

		if (SlotRight) {
			FVector2D Position = (FixedVelocity > 0.f) ? FVector2D(FixedVelocity - 5, 0.f) : DefaultPosition;
			SlotRight->SetPosition(Position);
		}
	}
}

void USoldierInterfaceWidget::SetVisibleCrosshair(bool bIsVisible) {
	if (SB_Top && SB_Bottom && SB_Left && SB_Right) {
		USizeBox* elements[4] = { SB_Top, SB_Bottom, SB_Left, SB_Right };
		if (bIsVisible) {
			for (USizeBox* i : elements)
				i->SetVisibility(ESlateVisibility::Hidden);
			GetWorld()->GetTimerManager().ClearTimer(TCrosshairHandle);
		}else {
			for (USizeBox* i : elements)
				i->SetVisibility(ESlateVisibility::Visible);
			GetWorld()->GetTimerManager().SetTimer(TCrosshairHandle, this, &USoldierInterfaceWidget::DynamicCrosshair, 1 / UpdatedPerSecond, true);
		}
	}
}