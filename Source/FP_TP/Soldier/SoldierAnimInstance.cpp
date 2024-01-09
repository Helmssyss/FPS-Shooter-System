#include "SoldierAnimInstance.h"
#include "../Soldier/Soldier.h"
#include "GameFramework/CharacterMovementComponent.h"

void USoldierAnimInstance::NativeUpdateAnimation(float DeltaSeconds) {
    Super::NativeUpdateAnimation(DeltaSeconds);
    if (ASoldier* TryPawn = Cast<ASoldier>(this->TryGetPawnOwner())) {
        soldierSpeed = TryPawn->GetVelocity().Size();
        soldierIsAir = TryPawn->GetMovementComponent()->IsFalling();
        soldierDirection = CalculateDirection(TryPawn->GetVelocity(), TryPawn->GetActorRotation());
        GetLookRotation(TryPawn);
        const FRotator deltaRotator = TryPawn->GetBaseAimRotation() - TryPawn->GetActorRotation();
        soldierPitch = deltaRotator.Pitch;
        soldierAimDownSight = TryPawn->GetAimDownSightState();
    }
}

FRotator USoldierAnimInstance::GetLookRotation(ASoldier* soldier) {
    const FTransform pawnTransform = soldier->GetActorTransform();
    const FRotator pawnControlRotation = soldier->GetControlRotation();
    const FRotator inverseTransform = InverseTransformRotation(pawnTransform, pawnControlRotation);
    const FRotator makeRotator = FRotator(0.0f, FMath::ClampAngle(inverseTransform.Yaw, -70.0f, 70.0f), FMath::ClampAngle((inverseTransform.Pitch * -1.0f), -70.0f, 70.0f));
    SoldierHeadRotation = FMath::RInterpTo(SoldierHeadRotation, makeRotator, GetWorld()->GetDeltaSeconds(), 9.0f);
    return SoldierHeadRotation;
}

FRotator USoldierAnimInstance::InverseTransformRotation(const FTransform& Transform, FRotator Rotation) {
    return Transform.InverseTransformRotation(Rotation.Quaternion()).Rotator();
}