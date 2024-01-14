#include "MainMenuWidget.h"
#include "../Soldier/Soldier.h"
#include "./FP_TP/FP_TPGameInstance.h"
#include "WidgetEnums.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"

void UMainMenuWidget::NativeOnInitialized(){
	Super::NativeOnInitialized();
	GameInstance = Cast<UFP_TPGameInstance>(GetGameInstance());

	StartButton->OnClicked.AddDynamic(this, &UMainMenuWidget::OpenMainBaseLevel);
	SelectAssaultClassButton->OnClicked.AddDynamic(this, &UMainMenuWidget::SelectAssaultClass);
	SelectSupportClassButton->OnClicked.AddDynamic(this, &UMainMenuWidget::SelectSupportClass);
	AK47_Select->OnClicked.AddDynamic(this, &UMainMenuWidget::AK47Select);
	AR4_Select->OnClicked.AddDynamic(this, &UMainMenuWidget::AR4Select);
}

void UMainMenuWidget::OpenMainBaseLevel(){
	if (GameInstance) {
		GameInstance->SoldierStaticClass = ASoldier::StaticClass();
		GameInstance->selectSoldierClass = selectSoldierClass;
		GameInstance->selectWeaponClass = selectWeaponClass;
		UGameplayStatics::OpenLevel(GetWorld(), FName("MainMap"));
	}
}

void UMainMenuWidget::AR4Select() { selectWeaponClass = ESoldierSelectWepon::WEAPON_AR4; }
void UMainMenuWidget::AK47Select() { selectWeaponClass = ESoldierSelectWepon::WEAPON_AK47; }
void UMainMenuWidget::SelectAssaultClass() { selectSoldierClass = ESoldierClasses::ASSAULT; }
void UMainMenuWidget::SelectSupportClass() { selectSoldierClass = ESoldierClasses::SUPPORT; }

//void UMainMenuWidget::SelectReconClass(){selectSoldierClass = ESoldierClasses::RECON;}
