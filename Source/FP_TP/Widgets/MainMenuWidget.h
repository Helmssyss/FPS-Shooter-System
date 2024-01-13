#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WidgetEnums.h"
#include "MainMenuWidget.generated.h"

class ASoldier;

class UButton;
class UFP_TPGameInstance;

UCLASS()
class FP_TP_API UMainMenuWidget : public UUserWidget{
	public:
		virtual void NativeConstruct() override;
	private:
		GENERATED_BODY()

		UFUNCTION()
		void OpenMainBaseLevel();

		UFUNCTION()
		void SelectAssaultClass();

		UFUNCTION()
		void SelectSupportClass();

		UFUNCTION()
		void AR4Select();

		UFUNCTION()
		void AK47Select();

		//UFUNCTION()
		//void SelectReconClass();

		UPROPERTY(meta = (BindWidget))
		UButton *StartButton;

		UPROPERTY(meta = (BindWidget))
		UButton* SelectAssaultClassButton;

		UPROPERTY(meta = (BindWidget))
		UButton* SelectSupportClassButton;

		//UPROPERTY(meta = (BindWidget))
		//UButton* SelectReconClassButton;

		UPROPERTY(meta = (BindWidget))
		UButton *AR4_Select;

		UPROPERTY(meta = (BindWidget))
		UButton *AK47_Select;

		ASoldier *Soldier;

		ESoldierSelectWepon selectWeaponClass;
		ESoldierClasses selectSoldierClass;
		UFP_TPGameInstance *GameInstance;
};
