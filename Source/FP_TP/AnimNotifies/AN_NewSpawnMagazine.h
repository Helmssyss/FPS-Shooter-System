// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "AN_NewSpawnMagazine.generated.h"

class ASoldier;

UCLASS()
class FP_TP_API UAN_NewSpawnMagazine : public UAnimNotify{
	public:
		virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;

	private:
		GENERATED_BODY()

		ASoldier* Soldier;
	
};
