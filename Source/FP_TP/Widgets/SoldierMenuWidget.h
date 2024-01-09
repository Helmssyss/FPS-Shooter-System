#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SoldierMenuWidget.generated.h"

class UTextBlock;
class UImage;
class ASoldier;

UCLASS()
class FP_TP_API USoldierMenuWidget : public UUserWidget{
	private:
		GENERATED_BODY()

		virtual void NativeConstruct() override;
		virtual bool Initialize() override;

		UFUNCTION()
		FText ViewWeaponCurrentAmmo();

		UFUNCTION()
		FText ViewWeaponTotalAmmo();

		UFUNCTION()
		FText ViewWeaponName();

		UFUNCTION()
		FSlateBrush ViewWeaponImage();

		UFUNCTION()
		FSlateBrush ViewWeaponFireMode();

		UPROPERTY(meta = (BindWidget))
		UImage *WeaponImage;

		UPROPERTY(meta = (BindWidget))
		UImage *FireModeImage;

		UPROPERTY(meta = (BindWidget))
		UTextBlock *WeaponName;

		UPROPERTY(meta = (BindWidget))
		UTextBlock *WeaponCurrentAmmo;

		UPROPERTY(meta = (BindWidget))
		UTextBlock *WeaponTotalAmmo;
		
		ASoldier *Soldier;
};
