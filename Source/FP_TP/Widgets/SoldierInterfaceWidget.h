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
class ASoldier;

UCLASS()
class FP_TP_API USoldierInterfaceWidget : public UUserWidget{
	
	public:
		UPROPERTY(meta = (BindWidget))
		UImage *WeaponImage;

		UPROPERTY(meta = (BindWidget))
		UImage *FireModeImage;

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

		float TestVelocity = 0.f;
		float MaxVelocity = 350.f;
		float MaxOffset = 100.f;
		float UpdatedPerSecond = 60.f;

		void SetVisibleCrosshair(bool bIsVisible);

	private:
		GENERATED_BODY()

		virtual void NativeConstruct() override;
		virtual void NativeOnInitialized() override;

		UFUNCTION()
		FText ViewTotalBulletCount();

		UFUNCTION()
		FText ViewCurrentBulletCount();

		UFUNCTION()
		FSlateBrush ViewWeaponImage();

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
