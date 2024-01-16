#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WeaponCustomizeWidget.generated.h"

class UButton;
class UFP_TPGameInstance;

UCLASS()
class FP_TP_API UWeaponCustomizeWidget : public UUserWidget{
	public:

		UPROPERTY(meta = (BindWidget))
		UButton *SelectSuppressor;

		UPROPERTY(meta = (BindWidget))
		UButton *UnSelectSuppressor;

		UPROPERTY(meta = (BindWidget))
		UButton *SelectRedDotSight;

		UPROPERTY(meta = (BindWidget))
		UButton *UnSelectSight;

	private:
		GENERATED_BODY()
		virtual void NativeOnInitialized() override;

		UFUNCTION()
		void SetSelectSuppressor();

		UFUNCTION()
		void SetUnSelectSuppressor();

		UFUNCTION()
		void SetSelectRedDotSight();

		UFUNCTION()
		void SetUnSelectSight();

		UFP_TPGameInstance *GameInstance;

		bool bSelectSuppressor;
		bool bSelectSight;
};
