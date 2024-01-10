// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "FP_Rifle_AN_NewSpawnMagazine.generated.h"

class ASoldier;

UCLASS()
class FP_TP_API UFP_Rifle_AN_NewSpawnMagazine : public UAnimNotify{
	public:
		virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;

	private:
		GENERATED_BODY()

		ASoldier* Soldier;
	
};
