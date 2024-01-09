#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseBulletInterface.h"
#include "Bullet762.generated.h"

class UStaticMeshComponent;
class UProjectileMovementComponent;
class USphereComponent;
class UAudioComponent;

UCLASS()
class FP_TP_API ABullet762 : public AActor, public IBaseBulletInterface{
	public:
		ABullet762();

		virtual UStaticMeshComponent* GetBulletMesh() override { return bulletMesh; }
		virtual UProjectileMovementComponent* GetBulletProjectileComponent() override { return bulletProjectile; }
		virtual USphereComponent* GetBulletSphere() override { return bulletSphere; }
		virtual UAudioComponent* GetBulletAudioCurve() override { return bulletAudioCurve; }
		virtual void BulletImpactParticle(UPrimitiveComponent* OtherComp, const FHitResult& Hit) override {}
		virtual void DestroyBullet() override;

	private:
		GENERATED_BODY()
		virtual void Tick(float DeltaTime) override;
		virtual void BeginPlay() override;

		UStaticMeshComponent* bulletMesh;
		UProjectileMovementComponent *bulletProjectile;
		USphereComponent *bulletSphere;
		UAudioComponent *bulletAudioCurve;
};
