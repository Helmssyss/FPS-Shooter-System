#include "MainMenuLevel.h"
#include "../Widgets/MainMenuWidget.h"
#include "UObject/ConstructorHelpers.h"

AMainMenuLevel::AMainMenuLevel(){
	const static ConstructorHelpers::FClassFinder<UUserWidget> MainMenuWidgetClass(TEXT("/Game/Widgets/BP_MainMenuWidget"));
	TMainMenuWidgetClass = MainMenuWidgetClass.Class;
}

void AMainMenuLevel::BeginPlay(){
	Super::BeginPlay();
	MainMenuWidget = CreateWidget<UMainMenuWidget>(GetWorld()->GetFirstPlayerController(), TMainMenuWidgetClass);
	MainMenuWidget->AddToViewport();
}
