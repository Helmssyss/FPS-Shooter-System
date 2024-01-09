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
		void SelectReconClass();

		UPROPERTY(meta = (BindWidget))
		UButton *StartButton;

		UPROPERTY(meta = (BindWidget))
		UButton* SelectAssaultClassButton;

		UPROPERTY(meta = (BindWidget))
		UButton* SelectSupportClassButton;

		UPROPERTY(meta = (BindWidget))
		UButton* SelectReconClassButton;

		ASoldier *Soldier;

		ESoldierClasses selectSoldierClass;
		UFP_TPGameInstance *GameInstance;
};
