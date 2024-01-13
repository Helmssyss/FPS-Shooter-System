#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BulletsEnum.h"
#include "EjectBullet.generated.h"

class URotatingMovementComponent;
class UProjectileMovementComponent;
class UStaticMeshComponent;

UCLASS()
class FP_TP_API AEjectBullet : public AActor{
	public:	
		AEjectBullet();
		void SetEjectBulletMesh(EBulletsEjectType ejectType);

	private:
		GENERATED_BODY()
		virtual void BeginPlay() override;
		virtual void Tick(float DeltaTime) override;

		UFUNCTION()
		void EjectBulletHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

		UStaticMeshComponent* EjectMesh;
		URotatingMovementComponent* BulletRotatingMovementComponent;
		UProjectileMovementComponent* projectileMovement;
};
