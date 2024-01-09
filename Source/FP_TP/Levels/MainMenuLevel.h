#pragma once

#include "CoreMinimal.h"
#include "Engine/LevelScriptActor.h"
#include "MainMenuLevel.generated.h"

class UMainMenuWidget;

UCLASS()
class FP_TP_API AMainMenuLevel : public ALevelScriptActor{
	public:
		AMainMenuLevel();

	private:
		GENERATED_BODY()
		virtual void BeginPlay() override;

		UPROPERTY(EditDefaultsOnly, Category = Widgets, meta = (AllowPrivateAccess = "true"))
		TSubclassOf<UMainMenuWidget> TMainMenuWidgetClass;

		UPROPERTY()
		UMainMenuWidget* MainMenuWidget;
};
