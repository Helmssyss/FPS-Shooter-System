#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SoldierInterfaceWidget.generated.h"

class UTextBlock;
class UImage;
class USizeBox;
class UCanvasPanelSlot;
class UFP_TPGameInstance;
class UWidgetAnimation;
class UHorizontalBox;
class ASoldier;

UCLASS()
class FP_TP_API USoldierInterfaceWidget : public UUserWidget{
	
	public:
		void SetVisibleCrosshair(bool bIsVisible);

		UPROPERTY(meta = (BindWidget))
		UImage *SecondaryWeaponImage;

		UPROPERTY(meta = (BindWidget))
		UImage *PrimaryWeaponImage;

		UPROPERTY(meta = (BindWidget))
		UImage *FireModeImage;

		UPROPERTY(meta = (BindWidget))
		UImage *CancelImage;

		UPROPERTY(meta = (BindWidget))
		UTextBlock *TotalBulletCount;

		UPROPERTY(meta = (BindWidget))
		UTextBlock *CurrentBulletCount;

		UPROPERTY(BlueprintReadOnly,meta = (BindWidget))
		USizeBox *SB_Top;

		UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		USizeBox *SB_Bottom;

		UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		USizeBox *SB_Left;

		UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		USizeBox *SB_Right;

		UPROPERTY(Transient, meta = (BindWidgetAnim))
		UWidgetAnimation *FireSpreadCrossHair;

		UPROPERTY(Transient, meta = (BindWidgetAnim))
		UWidgetAnimation *SelectHideWeaponImages;

		UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		UHorizontalBox *HPrimaryWeaponBox;

		UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		UHorizontalBox *HSecondaryWeaponBox;

		float MaxVelocity = 350.f;
		float MaxOffset = 100.f;
		float UpdatedPerSecond = 60.f;

	private:
		GENERATED_BODY()

		virtual void NativeConstruct() override;
		virtual void NativeOnInitialized() override;

		UFUNCTION()
		FText ViewTotalBulletCount();

		UFUNCTION()
		FText ViewCurrentBulletCount();

		UFUNCTION()
		FSlateBrush ViewPrimaryWeaponImage();

		UFUNCTION()
		FSlateBrush ViewSecondaryWeaponImage();

		UFUNCTION()
		FSlateBrush ViewWeaponFireMode();

		UFUNCTION()
		void DynamicCrosshair();

		UFP_TPGameInstance *GameInstance;
		FTimerHandle TCrosshairHandle;
		UCanvasPanelSlot *SlotTop;
		UCanvasPanelSlot *SlotBottom;
		UCanvasPanelSlot *SlotLeft;
		UCanvasPanelSlot *SlotRight;
};
