// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SoldierInterfaceWidget.generated.h"

class UTextBlock;
class UImage;
class ASoldier;
class UFP_TPGameInstance;

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

	private:
		GENERATED_BODY()

		virtual void NativeOnInitialized() override;

		UFUNCTION()
		FText ViewTotalBulletCount();

		UFUNCTION()
		FText ViewCurrentBulletCount();

		UFUNCTION()
		FSlateBrush ViewWeaponImage();

		UFUNCTION()
		FSlateBrush ViewWeaponFireMode();

		UFP_TPGameInstance *GameInstance;
};
