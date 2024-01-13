#include "MainMenuWidget.h"
#include "../Soldier/Soldier.h"
#include "./FP_TP/FP_TPGameInstance.h"
#include "WidgetEnums.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"

void UMainMenuWidget::NativeConstruct(){
	Super::NativeConstruct();
	StartButton->OnClicked.AddDynamic(this, &UMainMenuWidget::OpenMainBaseLevel);
	SelectAssaultClassButton->OnClicked.AddDynamic(this, &UMainMenuWidget::SelectAssaultClass);
	SelectSupportClassButton->OnClicked.AddDynamic(this, &UMainMenuWidget::SelectSupportClass);
	AK47_Select->OnClicked.AddDynamic(this, &UMainMenuWidget::AK47Select);
	AR4_Select->OnClicked.AddDynamic(this, &UMainMenuWidget::AR4Select);
	//SelectReconClassButton->OnClicked.AddDynamic(this, &UMainMenuWidget::SelectReconClass);

	Soldier = Cast<ASoldier>(GetOwningPlayerPawn());
	GameInstance = Cast<UFP_TPGameInstance>(GetGameInstance());

	if (Soldier) {
		APlayerController* controller = Cast<APlayerController>(Soldier->GetController());

		FInputModeGameOnly InputMode;
		controller->SetInputMode(InputMode);
		controller->bShowMouseCursor = true;
	}
}

void UMainMenuWidget::OpenMainBaseLevel(){
	if (GameInstance) {
		GEngine->AddOnScreenDebugMessage(-1, 2, FColor::Cyan, FString("GAMEINSTANCE GELDI"));
		GameInstance->SoldierStaticClass = Soldier->StaticClass();
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
