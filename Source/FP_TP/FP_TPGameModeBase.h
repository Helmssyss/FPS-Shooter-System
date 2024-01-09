#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "FP_TPGameModeBase.generated.h"

UCLASS()
class FP_TP_API AFP_TPGameModeBase : public AGameModeBase{
	public:
		AFP_TPGameModeBase();
	private:
		GENERATED_BODY()
		virtual void BeginPlay() override;
};
