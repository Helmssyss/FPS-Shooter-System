// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseBulletInterface.h"
#include "Bullet9.generated.h"

class UStaticMeshComponent;
class UProjectileMovementComponent;
class USphereComponent;
class UAudioComponent;
class UParticleSystemComponent;

UCLASS()
class FP_TP_API ABullet9 : public AActor, public IBaseBulletInterface {
	public:
		ABullet9();

		virtual UStaticMeshComponent* GetBulletMesh() override { return bulletMesh; }
		virtual UProjectileMovementComponent* GetBulletProjectileComponent() override { return bulletProjectile; }
		virtual USphereComponent* GetBulletSphere() override { return bulletSphere; }
		virtual UAudioComponent* GetBulletAudioCurve() override { return bulletAudioCurve; }
		virtual void BulletImpactParticle(UPrimitiveComponent* OtherComp, const FHitResult& Hit) override;
		virtual void DestroyBullet() override;

	private:
		GENERATED_BODY()

		UFUNCTION()
		void BulletHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

		virtual void Tick(float DeltaTime) override;
		virtual void BeginPlay() override;

		UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Soldier, meta = (AllowPrivateAccess = "true"))
		UStaticMeshComponent* bulletMesh;

		UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Soldier, meta = (AllowPrivateAccess = "true"))
		UProjectileMovementComponent* bulletProjectile;

		UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Soldier, meta = (AllowPrivateAccess = "true"))
		USphereComponent* bulletSphere;

		UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Soldier, meta = (AllowPrivateAccess = "true"))
		UAudioComponent* bulletAudioCurve;

		UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Soldier, meta = (AllowPrivateAccess = "true"))
		UParticleSystemComponent* bulletTrail;
};
