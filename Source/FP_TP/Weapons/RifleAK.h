// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RifleAK.generated.h"

UCLASS()
class FP_TP_API ARifleAK : public AActor{
	public:	
		ARifleAK();

	private:
		GENERATED_BODY()
		virtual void BeginPlay() override;
		virtual void Tick(float DeltaTime) override;
};
