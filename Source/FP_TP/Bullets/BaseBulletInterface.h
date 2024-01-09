#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "BaseBulletInterface.generated.h"

class UStaticMeshComponent;
class UProjectileMovementComponent;
class USphereComponent;
class UAudioComponent;

UINTERFACE(MinimalAPI)
class UBaseBulletInterface : public UInterface{GENERATED_BODY()};

class FP_TP_API IBaseBulletInterface{
	public:
		virtual UStaticMeshComponent* GetBulletMesh(void) = 0;
		virtual UProjectileMovementComponent* GetBulletProjectileComponent(void) = 0;
		virtual USphereComponent* GetBulletSphere(void) = 0;
		virtual UAudioComponent* GetBulletAudioCurve(void) = 0;
		virtual void BulletImpactParticle(UPrimitiveComponent *OtherComp, const FHitResult &Hit) = 0;
		virtual void DestroyBullet(void) = 0;

	private:
		GENERATED_BODY()
};
